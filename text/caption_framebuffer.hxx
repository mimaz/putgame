/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __caption_framebuffer_hxx
#define __caption_framebuffer_hxx

#include <putgame/common>
#include <putgame/glutils>

namespace text
{
    class buffered_caption;

    class caption_framebuffer : public common::context::part
    {
    public:
        caption_framebuffer(common::context *ctx);
        ~caption_framebuffer();

        void begin(GLuint texhandle, 
                   buffered_caption *capt);
        void draw(const glm::mat4 &matrix);
        void end();

    private:
        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;
        glutils::attribute a_coord;
        glutils::uniform u_color;
        glutils::uniform u_text_color;
        glutils::uniform u_matrix;

        GLuint fbhandle;
    };
}

#endif
