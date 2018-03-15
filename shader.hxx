/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __glutils_shader_hxx
#define __glutils_shader_hxx

namespace glutils
{
    class shader
    {
    public:
        using srcitem = const GLchar *;
        using srclist = std::initializer_list<srcitem>;
        using srcvec = std::vector<srcitem>;

        shader(GLenum type, const srclist &list);

          template<typename ..._Sources>
        shader(GLenum type, const _Sources &...sources);

        shader(const shader &) = delete;
        shader(shader &&) = default;

        ~shader();

        void compile();
        void destroy();

        GLuint get_handle();

    private:
        GLenum type;
        srcvec srcv;

        GLuint handle;
    };

      template<typename ..._Sources>
    shader::shader(GLenum type, const _Sources &...sources)
        : shader(type, { sources... }) {}
}

#endif
