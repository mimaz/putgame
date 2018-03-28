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
        set_back_normal_color({ 0.5f, 0.5f, 0.5f, 0.5f });
        set_back_highlight_color({ 0.25f, 0.25f, 0.25f, 0.5f });
        set_text_normal_color({ 1.0f, 1.0f, 0.0f, 1.0f });
        set_text_highlight_color({ 0.0f, 1.0f, 1.0f, 1.0f });

        shadows.push_back(glm::vec4(0.4f, 0.1f, 0.9f, 0.8f));
    }

    void color_button::set_back_normal_color(glm::vec4 color)
	{
        colors[color_button_view::back_normal] = color;
	}

    void color_button::set_back_highlight_color(glm::vec4 color)
	{
        colors[color_button_view::back_highlight] = color;
	}

    void color_button::set_text_normal_color(glm::vec4 color)
	{
        colors[color_button_view::text_normal] = color;
	}

    void color_button::set_text_highlight_color(glm::vec4 color)
	{
        colors[color_button_view::text_highlight] = color;
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
