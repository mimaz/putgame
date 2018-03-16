/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __glutils_attribute_hxx
#define __glutils_attribute_hxx

namespace glutils
{
    class program;

    class attribute
    {
    public:
        attribute(program *prog, const GLchar *name);

        GLuint get_handle();

        void enable();
        void disable();

        operator GLuint() { return get_handle(); }

    private:
        program *const prog;
        const GLchar *const name;

        bool bound;
        GLint handle;
    };
}

#endif
