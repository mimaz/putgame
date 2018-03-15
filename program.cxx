/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std.hxx>

#include "program.hxx"

#include "shader.hxx"

namespace glutils
{
    program::program(const shdlist &list)
        : shdv(list.begin(), list.end()), handle(0) {}

    program::~program()
    {
        destroy();
    }

    void program::link()
    {
        destroy();

        handle = glCreateProgram();

        for (shader *sh : shdv)
            glAttachShader(handle, *sh);

        glLinkProgram(handle);

        GLint ok;


        glGetProgramiv(handle, GL_LINK_STATUS, &ok);


        if (not ok)
        {
            GLchar msg[256];

            glGetProgramInfoLog(handle, sizeof(msg), nullptr, msg);

            std::cerr << "linking program failed: " << msg << std::endl;

            exit(1);
        }
    }

    void program::destroy()
    {
        if (handle > 0)
            glDeleteProgram(handle);

        handle = 0;
    }

    GLuint program::get_handle()
    {
        if (handle <= 0)
            link();

        return handle;
    }
}
