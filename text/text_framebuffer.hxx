/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __text_framebuffer_hxx
#define __text_framebuffer_hxx

#include <putgame/common>
#include <putgame/glutils>

namespace text
{
    class text_buffer;

    class text_framebuffer : public common::context::part
    {
    public:
        text_framebuffer(common::context *ctx);
        ~text_framebuffer();

        void begin(GLuint texhandle, 
                   text_buffer *capt);
        void draw(const glm::mat4 &matrix);
        void end();

    private:
        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;
        glutils::attribute a_coord;
        glutils::uniform u_matrix;

        GLuint fbhandle;
    };
}

#endif
