/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "main_menu.hxx"

main_menu::main_menu(common::context *ctx)
    : rect_item(ctx)
    , start_button(ctx)
    , leaderboard_button(ctx)
    , achievements_button(ctx)
{
    auto primary = glm::vec4(0.15f, 0.15f, 0.15f, 0.75f);

    start_button.set_text("start");
    start_button.set_primary_color(primary);
    start_button.set_secondary_color(glm::vec4(1, 1, 0, 0.5f));

    leaderboard_button.set_text("leaderboards");
    leaderboard_button.set_primary_color(primary);
    leaderboard_button.set_secondary_color(glm::vec4(1, 0, 1, 0.5f));

    achievements_button.set_text("achievements");
    achievements_button.set_primary_color(primary);
    achievements_button.set_secondary_color(glm::vec4(0, 1, 1, 0.5f));
}

void main_menu::on_surface_resize(int w, int h)
{
    gui::rect_item::on_surface_resize(w, h);

    auto btn_height = h / 6;
    auto btn_width = btn_height * 5;

    auto btn_posx = w / 2 - btn_width / 2;

    start_button.resize(btn_width, btn_height);
    start_button.set_position(btn_posx, btn_height * 2);

    leaderboard_button.resize(btn_width, btn_height);
    leaderboard_button.set_position(btn_posx, 0);

    achievements_button.resize(btn_width, btn_height);
    achievements_button.set_position(btn_posx, -btn_height * 2);
}
