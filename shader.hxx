/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __common_shader_hxx
#define __common_shader_hxx

namespace common
{
    class shader
    {
    public:
        using srcitem = const GLchar *;
        using srcvec = std::vector<srcitem>;

        shader(GLenum type, srcitem src);
        shader(GLenum type, srcvec src);

        void compile();
        void destroy();

        GLuint get_handle();

    private:
        GLenum type;
        std::vector<const GLchar *> srcv;

        GLuint handle;
    };
}

#endif
