/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "wall_obstacle.hxx"

#include "context.hxx"
#include "wall_obstacle_manager.hxx"

namespace 
{
    constexpr auto scale_factor = 0.1f;
}

namespace world
{
    wall_obstacle::wall_obstacle(context *ctx, 
                                 int w, int h, int d)
        : visible_object(ctx)
        , width(w)
        , height(h)
        , depth(d)
    {
        auto xscale = w * scale_factor;
        auto yscale = h * scale_factor;
        auto zscale = d * scale_factor;

        scale(glm::vec3(xscale, yscale, zscale));

        get_context()->get_part<wall_obstacle_manager>()->add(this);
    }

    wall_obstacle::~wall_obstacle()
    {
        get_context()->get_part<wall_obstacle_manager>()->remove(this);
    }
}
