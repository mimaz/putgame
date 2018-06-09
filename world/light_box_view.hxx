/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_light_box_view_hxx
#define __world_light_box_view_hxx

#include <putgame/common>

#include "lighting.hxx"

namespace world
{
    class camera;
    class lighting;
    class light_box;

    class light_box_view
    {
    public:
        static constexpr auto boxes_per_draw = 4;

        static const float mesh[];
        static const size_t size_of_mesh;

        light_box_view(common::context *ctx);

        light_box_view(const light_box_view &) = delete;
        light_box_view(light_box_view &&) = delete;

        void begin_drawing();
        void draw_element(const light_box *box);
        void end_drawing();

    private:
        void draw_instances();

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program prog;
        glutils::attribute a_coord;
        glutils::attribute a_normal;
        glutils::uniform u_type;
        glutils::uniform u_model_v;
        glutils::uniform u_mvp_v;
        glutils::uniform u_color_v;
        glutils::buffer vbo;

        lighting light;

        camera *cam;

        std::array<glm::mat4, boxes_per_draw> models;
        std::array<glm::mat4, boxes_per_draw> mvps;
        std::array<glm::vec3, boxes_per_draw> colors;

        int count;
    };
}

#endif
