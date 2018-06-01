/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>

#include "program.hxx"

#include "shader.hxx"

namespace glutils
{
    program::program(const std::string &tag,
                     const shdlist &list)
        : tag(tag)
        , shdv(list.begin(), list.end()), handle(0) {}

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

            common::loge("linking program failed: ", msg);

            exit(1);
        }
    }

    void program::destroy()
    {
        if (handle > 0)
            glDeleteProgram(handle);

        handle = 0;
    }

    void program::use()
    {
        glUseProgram(get_handle());
    }

    std::string program::get_tag()
    {
        return tag;
    }

    GLuint program::get_handle()
    {
        if (handle <= 0)
            link();

        return handle;
    }
}
