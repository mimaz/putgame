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

        uniform(const uniform &) = delete;
        uniform(uniform &&) = delete;

        GLuint get_handle();

        operator GLuint() { return get_handle(); }

        void operator=(const GLfloat &);
        void operator=(const GLint &);
        void operator=(const GLuint &);
        void operator=(const glm::vec2 &);
        void operator=(const glm::vec3 &);
        void operator=(const glm::vec4 &);
        void operator=(const glm::mat4 &);

    private:
        program *const prog;
        const GLchar *const name;

        GLint handle;
        bool bound;
    };
}

#endif
