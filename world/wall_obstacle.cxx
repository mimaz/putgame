/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */


#include "wall_obstacle.hxx"

#include "object_manager.hxx"

namespace world
{
    constexpr auto scale_factor = 0.1f;

    wall_obstacle::wall_obstacle(common::context *ctx, 
                                 int frameid,
                                 int w, int h, int d)
        : visible_object(ctx, frameid)
        , width(w)
        , height(h)
        , depth(d)
    {
        auto xscale = w * scale_factor;
        auto yscale = h * scale_factor;
        auto zscale = d * scale_factor;

        scale(xscale, yscale, zscale);

        get<object_manager>()->add(this);
    }

    wall_obstacle::~wall_obstacle()
    {
        get<object_manager>()->remove(this);
    }
}
