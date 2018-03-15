/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std.hxx>

#include "attribute.hxx"

#include "program.hxx"

namespace glutils
{
    attribute::attribute(program *prog, const GLchar *name)
        : prog(prog), name(name), handle(0) {}

    GLuint attribute::get_handle()
    {
        if (handle == 0)
            handle = glGetAttribLocation(*prog, name);

        return static_cast<GLuint>(handle);
    }

    void attribute::enable()
    {
        glEnableVertexAttribArray(get_handle());
    }

    void attribute::disable()
    {
        glDisableVertexAttribArray(get_handle());
    }
}
