/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "glass_pane.hxx"

#include "glass_manager.hxx"
#include "context.hxx"

namespace world
{
    glass_pane::glass_pane(context *ctx,
                           common::rgb_color col, 
                           glm::vec2 siz)
        : visible_object(ctx)
        , color(col)
        , size(siz)
    {
        ctx->get_part<glass_manager>()->add(this);
    }

    glass_pane::~glass_pane()
    {
        get_context()->get_part<glass_manager>()->remove(this);
    }
}
