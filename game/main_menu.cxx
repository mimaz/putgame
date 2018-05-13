/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "main_menu.hxx"

namespace game
{
    main_menu::main_menu(common::context *ctx)
        : rect_item(ctx)
        , start_btn(ctx)
        , leaderboard_btn(ctx)
        , achievements_btn(ctx)
    {
        auto primary = glm::vec4(0.15f, 0.15f, 0.15f, 0.75f);

        start_btn.set_text("0123456789");
        start_btn.set_primary_color(primary);
        start_btn.set_secondary_color(glm::vec4(1, 1, 0, 0.5f));

        leaderboard_btn.set_text("!@#$%^&*()");
        leaderboard_btn.set_primary_color(primary);
        leaderboard_btn.set_secondary_color(glm::vec4(1, 0, 1, 0.5f));

        achievements_btn.set_text("mnoprstuvwxyz");
        achievements_btn.set_primary_color(primary);
        achievements_btn.set_secondary_color(glm::vec4(0, 1, 1, 0.5f));
    }

    void main_menu::on_surface_resize(int w, int h)
    {
        gui::rect_item::on_surface_resize(w, h);

        auto btn_height = h / 6;
        auto btn_width = btn_height * 5;

        auto btn_posx = w / 2 - btn_width / 2;

        start_btn.resize(btn_width, btn_height);
        start_btn.set_position(btn_posx, btn_height * 2);

        leaderboard_btn.resize(btn_width, btn_height);
        leaderboard_btn.set_position(btn_posx, 0);

        achievements_btn.resize(btn_width, btn_height);
        achievements_btn.set_position(btn_posx, -btn_height * 2);
    }
}
