/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __main_menu_hxx
#define __main_menu_hxx

#include <putgame/gui>

class main_menu : public gui::rect_item
{
public:
    main_menu(common::context *ctx);

    void on_surface_resize(int w, int h) override;

private:
    gui::color_button start_button;
    gui::color_button leaderboard_button;
    gui::color_button achievements_button;
};

#endif
