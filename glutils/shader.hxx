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
        using srcitem = std::string;
        using srclist = std::initializer_list<srcitem>;
        using srcvec = std::vector<srcitem>;

        shader(const std::string &tag, 
               GLenum type, 
               const srclist &list);

          template<typename ..._Sources>
        shader(const std::string &tag,
               GLenum type, 
               const _Sources &...sources);

        shader(const shader &) = delete;
        shader(shader &&) = default;

        ~shader();

        void compile();
        void destroy();

        GLuint get_handle();

        operator GLuint() { return get_handle(); }

    private:
        std::string tag;
        GLenum type;
        srcvec srcv;

        GLuint handle;
    };

      template<typename ..._Sources>
    shader::shader(const std::string &tag,
                   GLenum type, 
                   const _Sources &...sources)
        : shader(tag, type, { sources... }) {}
}

#endif
