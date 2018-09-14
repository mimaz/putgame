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
        void set_scaling(float sc);
        void scale_up();
        void scale_down();

        void on_surface_resize(int w, int h) override;
        void draw() override;
        void resize(int w, int h) override;

    private:
        void create_texture();
        void destroy_texture();

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;
        glutils::attribute a_coord;
        glutils::attribute a_tex_coord;
        glutils::buffer vbo;

        GLuint fbhandle;
        GLuint rdhandle;
        GLuint txhandle;

        float scaling;
        bool dirty;
        int fbwidth;
        int fbheight;
        int vpdata[4];
    };
}

#endif
