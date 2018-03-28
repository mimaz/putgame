/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "color_button.hxx"

#include "color_button_view.hxx"
#include "surface.hxx"

namespace gui
{
    color_button::color_button(common::context *ctx)
        : rect_item(ctx)
        , text(ctx, get_part<surface>()->get_font_builder())
    {
        set_primary_color(glm::vec4(0.7f, 0.5f, 0.3f, 1.0f));
        set_secondary_color(glm::vec4(0.3f, 0.5f, 0.7f, 1.0));

        shadows.push_back(glm::vec4(0.4f, 0.1f, 0.9f, 0.8f));
    }

    void color_button::set_primary_color(glm::vec4 color)
    {
        primary_color = color;
    }

    void color_button::set_secondary_color(glm::vec4 color)
    {
        secondary_color = color;
    }

    void color_button::draw()
    {
        rect_item::draw();

        get_part<color_button_view>()->draw(this);
    }

    void color_button::preprocess()
    {
        rect_item::preprocess();
    }

    void color_button::bind_texture()
    {
        glBindTexture(GL_TEXTURE_2D, text.get_texture_handle());
    }

    void color_button::on_size_changed()
    {
        rect_item::on_size_changed();

        text.set_size(get_width(), get_height());
        text.set_font_size(get_width() / 6, get_height() / 6);
    }
}
