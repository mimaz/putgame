/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "color_button.hxx"

namespace gui
{
    color_button::color_button(common::context *ctx)
        : rect_item(ctx)
    {}

    void color_button::set_back_normal_color(glm::vec4 color)
	{
	}

    void color_button::set_back_highlight_color(glm::vec4 color)
	{
	}

    void color_button::set_text_normal_color(glm::vec4 color)
	{
	}

    void color_button::set_text_highlight_color(glm::vec4 color)
	{
	}
}
