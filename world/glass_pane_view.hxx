/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_glass_pane_view_hxx
#define __world_glass_pane_view_hxx

#include <putgame/common>

#include "lighting.hxx"

namespace world
{
    class camera;
    class glass_pane;

    class glass_pane_view
    {
    public:
        static constexpr auto instances_per_call = 4;

        glass_pane_view(common::context *ctx);

        void begin_drawing();
        void draw_element(const glass_pane *pane);
        void end_drawing();

    private:
        void draw();

        camera *cam;

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;
        glutils::attribute a_coord;
        glutils::uniform u_model_v;
        glutils::uniform u_mvp_v;
        glutils::uniform u_color_v;
        glutils::uniform u_specular_mode;
        glutils::buffer vbo;

        lighting light;

        std::array<glm::mat4, instances_per_call> models;
        std::array<glm::mat4, instances_per_call> mvps;
        std::array<glm::vec3, instances_per_call> colors;
        int instance_count;
    };
}

#endif
