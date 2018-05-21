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
        void layout(int w, int h);

        gui::color_button start_btn;
    };
}

#endif
