/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */


#include "attribute.hxx"

#include "program.hxx"
#include "exception.hxx"

namespace glutils
{
    attribute::attribute(program *prog, const GLchar *name)
        : prog(prog), name(name), bound(false) {}

    GLuint attribute::get_handle()
    {
        if (not bound)
        {
            bound = true;

            handle = glGetAttribLocation(*prog, name);

            if (handle < 0)
                throw location_error(prog->get_tag(), name);
        }

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
