/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_wall_obstacle_view_hxx
#define __world_wall_obstacle_view_hxx

#include <putgame/glutils>
#include <putgame/common>

#include "lighting.hxx"

namespace world
{
    class context;
    class camera;
    class lighting;
    class wall_obstacle;

    class wall_obstacle_view
    {
    public:
        static const float mesh[];
        static const size_t size_of_mesh;

        static const glm::vec3 primary_color;
        static const glm::vec3 secondary_color;

        static constexpr auto draw_instances = 4;


        wall_obstacle_view(context *ctx);
        ~wall_obstacle_view();

        void begin_drawing();
        void draw_element(const wall_obstacle *wall);
        void end_drawing();

    private:
        void draw_walls();

        camera *cam;
        glm::vec3 side_color;

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;
        glutils::attribute a_coord;
        glutils::attribute a_normal;
        glutils::attribute a_tex_coord;
        glutils::attribute a_mode;
        glutils::uniform u_model;
        glutils::uniform u_mvp;
        glutils::uniform u_tex_factor;
        glutils::uniform u_model_v;
        glutils::uniform u_mvp_v;
        glutils::uniform u_tex_factor_v;

        lighting light;

        GLuint texhandle;

        std::array<glm::mat4, draw_instances> models;
        std::array<glm::mat4, draw_instances> mvps;
        std::array<glm::vec2, draw_instances> tex_factors;
        int instance_count;
    };
}

#endif

