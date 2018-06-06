/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/res>

#include "lighting.hxx"

#include "camera.hxx"
#include "light_group.hxx"
#include "light_source.hxx"

namespace world
{
    const GLchar *const lighting::fragment_source = lighting_glsl;

    lighting::lighting(common::context *ctx, glutils::program *prog)
        : u_camera_coord(prog, "u_camera_coord")
        , u_view_range(prog, "u_view_range")
        , u_light_count(prog, "u_light_count")
        , u_light_coord_v(prog, "u_light_coord_v")
        , u_light_color_v(prog, "u_light_color_v")
        , u_light_range_v(prog, "u_light_range_v")
        , cam(ctx->get<camera>())
        , grp(ctx->get<light_group>())
    {}

    void lighting::calculate()
    {
        auto all = grp->get_all();
        auto count = (GLuint) all.size();

        glm::vec3 coords[count];
        glm::vec3 colors[count];
        GLfloat ranges[count];

        int idx = 0;

        for (auto s : all)
        {
            coords[idx] = s->get_light_position();
            colors[idx] = s->get_light_color();
            ranges[idx] = s->get_light_range();

            idx++;
        }

        try {
            u_camera_coord = cam->get_position();
            u_view_range = cam->get_view_range();
            u_light_count = count;

            glUniform3fv(u_light_coord_v, count, 
                         glm::value_ptr(coords[0]));

            glUniform3fv(u_light_color_v, count, 
                         glm::value_ptr(colors[0]));

            glUniform1fv(u_light_range_v, count, ranges);
        } catch(glutils::location_error e) {
            std::cerr << "location_error: " << e.name << std::endl;
        }
    }
}
