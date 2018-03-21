/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "wall_obstacle.hxx"

namespace 
{
    constexpr auto scale_factor = 0.1f;
}

namespace world
{
    wall_obstacle::wall_obstacle(context *ctx, int w, int h)
        : wall_obstacle(ctx, w, h, 1)
    {}

    wall_obstacle::wall_obstacle(context *ctx, 
                                 int w, int h, int d)
        : abstract_obstacle(ctx)
        , width(w)
        , height(h)
        , depth(d)
    {
        auto xscale = w * scale_factor;
        auto yscale = h * scale_factor;
        auto zscale = d * scale_factor;

        scale(glm::vec3(xscale, yscale, zscale));

        register_self(this);
    }
}
