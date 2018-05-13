/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_main_menu_hxx
#define __game_main_menu_hxx

#include <putgame/gui>

namespace game
{
    class main_menu : public gui::rect_item
    {
    public:
        main_menu(common::context *ctx);

        void on_surface_resize(int w, int h) override;

    private:
        gui::color_button start_btn;
        gui::color_button leaderboard_btn;
        gui::color_button achievements_btn;
    };
}

#endif
