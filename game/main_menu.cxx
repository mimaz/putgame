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
        , start_btn(ctx, std::bind(&main_menu::clicked, 
                    this, std::placeholders::_1))
        , exit_btn(ctx, std::bind(&main_menu::clicked,
                   this, std::placeholders::_1))
    {
        auto primary = glm::vec4(0.15f, 0.15f, 0.15f, 0.75f);

        start_btn.set_text("start!");
        start_btn.set_primary_color(primary);
        start_btn.set_secondary_color(glm::vec4(1, 0, 0, 0.5f));

        exit_btn.set_text("exit");
        exit_btn.set_primary_color(primary);
        exit_btn.set_secondary_color(glm::vec4(0, 0, 1, 0.5f));

        layout(ctx->get_width(), ctx->get_height());
    }

    void main_menu::on_surface_resize(int w, int h)
    {
        layout(w, h);
    }

    void main_menu::layout(int w, int h)
    {
        gui::rect_item::on_surface_resize(w, h);

        auto btnwidth = w / 2;
        auto btnheight = h / 6;

        start_btn.resize(btnwidth, btnheight);
        start_btn.set_position((btnwidth - w) / 2,
                               (btnheight - h) / 2);

        exit_btn.resize(btnwidth, btnheight);
        exit_btn.set_position((w - btnwidth) / 2,
                              (btnheight - h) / 2);
    }

    void main_menu::clicked(gui::color_button *btn)
    {
        common::logd("clicked");
    }
}
