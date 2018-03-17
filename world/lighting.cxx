/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std.hxx>
#include <putgame-res.h>

#include "lighting.hxx"

#include "camera.hxx"

#include <glutils/exception.hxx>

namespace world
{
    const GLchar *const lighting::fragment_source = lighting_fsh;

    lighting::lighting(context *ctx, glutils::program *prog)
        : u_camera_coord(prog, "u_camera_coord")
        , u_light_count(prog, "u_light_count")
        , u_light_coord_v(prog, "u_light_coord_v")
        , u_light_color_v(prog, "u_light_color_v")
        , u_light_range_v(prog, "u_light_range_v")
        , cam(ctx->get_part<camera>())
    {}

    void lighting::calculate()
    {
        glm::vec3 pos = { 0, 0, 0 };
        glm::vec3 col = { 1, 1, 1 };
        float ran = 10;

        try {
            u_light_count = 1;
            u_light_coord_v = pos;
            u_light_color_v = col;
            u_light_range_v = ran;

            u_camera_coord = cam->get_position();
        } catch(glutils::location_error e) {
            std::cerr << "location_error: " << e.name << std::endl;
        }
    }
}
