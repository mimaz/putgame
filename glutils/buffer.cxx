/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "buffer.hxx"
#include "exception.hxx"

namespace glutils
{
    buffer::buffer(GLenum type, const void *data, GLuint size)
        : type(type)
        , data(data)
        , size(size)
        , handle(0)
    {}

    buffer::~buffer()
    {
        if (handle!= 0)
            glDeleteBuffers(1, &handle);
    }

    void buffer::bind()
    {
        glBindBuffer(get_type(), get_handle());
    }

    GLuint buffer::get_handle()
    {
        if (handle == 0)
        {
            glGenBuffers(1, &handle);

            bind();


            glBufferData(get_type(), size, data, GL_STATIC_DRAW);
        }

        return handle;
    }
}
