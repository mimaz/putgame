/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __play_hud_hxx
#define __play_hud_hxx

#include <putgame/gui>

namespace game
{
    class play_hud : public gui::rect_item
    {
    public:
        play_hud(common::context *ctx);

        void on_surface_resize(int w, int h) override;

        void enable();
        void disable();

    private:
        void layout(int w, int h);

        gui::score_counter counter;
    };
}

#endif
