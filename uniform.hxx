/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __glutils_uniform_hxx
#define __glutils_uniform_hxx

namespace glutils
{
    class program;

    class uniform
    {
    public:
        uniform(program *prog, const GLchar *name);

        void detach();

        GLuint get_handle();

        void operator=(const glm::mat4 &);

    private:
        program *const prog;
        const GLchar *const name;

        GLint handle;
    };
}

#endif
