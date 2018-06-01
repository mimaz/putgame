/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_lighting_hxx
#define __world_lighting_hxx

#include <putgame/glutils>
#include <putgame/common>

namespace world
{
    class camera;
    class light_group;

    class lighting
    {
    public:
        static const GLchar *const fragment_source;

        lighting(common::context *ctx, glutils::program *prog);

        void calculate();

    private:
        glutils::uniform u_camera_coord;
        glutils::uniform u_view_range;
        glutils::uniform u_light_count;
        glutils::uniform u_light_coord_v;
        glutils::uniform u_light_color_v;
        glutils::uniform u_light_range_v;

        camera *cam;
        light_group *grp;
    };
}

#endif
