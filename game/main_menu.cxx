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
    {
        auto primary = glm::vec4(0.15f, 0.15f, 0.15f, 0.75f);

        start_btn.set_text("start!");
        start_btn.set_primary_color(primary);
        start_btn.set_secondary_color(glm::vec4(1, 1, 0, 0.5f));

        layout(ctx->get_width(), ctx->get_height());
    }

    void main_menu::on_surface_resize(int w, int h)
    {
        layout(w, h);
    }

    void main_menu::layout(int w, int h)
    {
        std::cout << "resize: " << w << ":" << h << std::endl;
        gui::rect_item::on_surface_resize(w, h);

        start_btn.resize(w / 2,  h / 8);
        start_btn.set_position(0, 0);
    }
}
