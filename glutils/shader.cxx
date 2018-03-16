/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std.hxx>

#include "shader.hxx"

#include "exception.hxx"

namespace glutils
{
    namespace 
    {
        std::string strtype(GLenum type)
        {
            std::string str;

            switch (type)
            {
            case GL_VERTEX_SHADER:
                str = "vertex";
                break;

            case GL_FRAGMENT_SHADER:
                str = "fragment";
                break;

            default:
                str = "unknown";
            }

            return str;
        }
    }

    shader::shader(GLenum type, const srclist &list)
        : type(type), srcv(list.begin(), list.end()), handle(0) {}

    shader::~shader() 
    {
        destroy();
    }

    void shader::compile()
    {
        destroy();


        handle = glCreateShader(type);
        
        if (handle < 1)
        {
            std::cerr << "creating shader of type " 
                      << strtype(type)
                      << "failed!" << std::endl;

            exit(1);
        }


        glShaderSource(handle, srcv.size(), srcv.data(), nullptr);
        glCompileShader(handle);


        GLint ok;
        glGetShaderiv(handle, GL_COMPILE_STATUS, &ok);


        if (not ok)
        {
            GLchar msg[256];

            glGetShaderInfoLog(handle, sizeof(msg), nullptr, msg);


            throw shader_error { type, msg };
        }
    }

    void shader::destroy()
    {
        if (handle > 0)
            glDeleteShader(handle);

        handle = 0;
    }

    GLuint shader::get_handle()
    {
        if (handle <= 0)
            compile();

        return handle;
    }
}

