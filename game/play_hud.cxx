/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include "play_hud.hxx"

namespace game
{
    play_hud::play_hud(common::context *ctx)
        : rect_item(ctx)
        , counter(ctx)
    {}

    void play_hud::on_surface_resize(int w, int h)
    {
        rect_item::on_surface_resize(w, h);

        layout(w, h);
    }

    void play_hud::enable()
    {
        common::logd("enable hud");
    }

    void play_hud::disable()
    {

    }

    void play_hud::layout(int w, int h)
    {
    }
}
