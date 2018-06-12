/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_frame_buffer_hxx
#define __world_frame_buffer_hxx

#include <putgame/gui>
#include <putgame/glutils>

namespace world
{
    class frame_buffer : public gui::rect_item
    {
    public:
        PUTGAME_OBJECT

        frame_buffer(common::context *ctx);
        ~frame_buffer();

        void bind();
        void unbind();
        void on_surface_resize(int w, int h) override;
        void draw() override;

    private:
        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;
        glutils::attribute a_coord;
        glutils::uniform u_matrix;

        GLuint fbhandle;
        GLuint rdhandle;
        GLuint txhandle;

        int vpdata[4];
    };
}

#endif
