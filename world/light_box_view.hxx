/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_light_box_view_hxx
#define __world_light_box_view_hxx

#include <glutils/program.hxx>
#include <glutils/shader.hxx>
#include <glutils/attribute.hxx>
#include <glutils/uniform.hxx>
#include <glutils/buffer.hxx>

#include "lighting.hxx"

namespace world
{
    class context;
    class camera;
    class lighting;
    class light_box;

    class light_box_view
    {
    public:
        light_box_view(context *ctx);

        light_box_view(const light_box_view &) = delete;
        light_box_view(light_box_view &&) = delete;

        void begin_drawing(bool stripped);
        void draw(const light_box *box);
        void end_drawing();

    private:
        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program prog;
        glutils::attribute a_coord;
        glutils::attribute a_normal;
        glutils::attribute a_type;
        glutils::uniform u_model;
        glutils::uniform u_mvp;
        glutils::uniform u_color;
        glutils::buffer vbo;

        std::unique_ptr<lighting> light;

        camera *cam;

        GLuint vertices;
    };
}

#endif
