/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_frame_buffer_hxx
#define __world_frame_buffer_hxx

#include <putgame/gui>

namespace world
{
    class frame_buffer : public gui::rect_item
    {
    public:
        PUTGAME_OBJECT

        frame_buffer(common::context *ctx);
        ~frame_buffer();

        void bind();
        void on_surface_resize(int w, int h) override;
        void draw() override;

    private:
        GLuint fbhandle;
        GLuint rdhandle;
        GLuint txhandle;
    };
}

#endif
