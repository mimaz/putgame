/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __glutils_buffer_hxx
#define __glutils_buffer_hxx

namespace glutils
{
    class buffer
    {
    public:
        buffer(GLenum type, const void *data, GLuint size);

        buffer(const buffer &) = delete;
        buffer(buffer &&) = default;

        ~buffer();

        void bind();

        GLenum get_type() const { return type; }
        GLuint get_handle();

        operator GLuint() { return get_handle(); }

    private:
        GLenum type;
        const void *data;
        GLuint size;

        GLuint handle;
    };
}

#endif
