/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "glass_pane.hxx"

namespace world
{
    glass_pane::glass_pane(context *ctx,
                           common::rgb_color col, 
                           glm::vec2 siz)
        : visible_object(ctx)
        , color(col)
        , size(siz)
    {}
}
