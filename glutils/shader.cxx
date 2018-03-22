/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

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
        : type(type), srcv(list.begin(), list.end()), handle(0) 
    {}

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


        const char *arr[srcv.size()];

        std::transform(srcv.begin(), srcv.end(), arr,
                       [](const srcitem &item) -> const char * {
            return item.c_str();
        });

        glShaderSource(handle, srcv.size(), arr, nullptr);
        glCompileShader(handle);


        GLint ok;
        glGetShaderiv(handle, GL_COMPILE_STATUS, &ok);


        if (not ok)
        {
            auto msgsize = 2048;
            auto msgptr = std::unique_ptr<char>(new char[msgsize]);
            auto msg = msgptr.get();


            glGetShaderInfoLog(handle, msgsize, nullptr, msg);


            std::string code;

            for (auto &s : srcv)
                code += s + "\n";


            auto log = std::string(msg);


            throw shader_error { type, log, std::move(code) };
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

