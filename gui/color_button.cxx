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
        set_primary_color(glm::vec4(1.0f, 1.0f, 0.5f, 1.0f));
        set_secondary_color(glm::vec4(0.4f, 0.4f, 0.4f, 1.0));
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

        constexpr auto show_speed = 0.025f;
        constexpr auto hide_speed = 0.0275f;

        auto count = static_cast<int>(shadows.size());

        for (auto i = 0; i < count; i++)
        {
            shadows[i][0] += show_speed;

            if (i > 0 or not is_pressed())
                shadows[i][1] += hide_speed;
        }


        auto newend = std::remove_if(shadows.begin(), shadows.end(),
                [](const glm::vec4 &v) -> bool {
                    return v[1] > sqrtf(2);
                });

        auto newsiz = std::distance(shadows.begin(), newend);

        shadows.resize(newsiz);
    }

    void color_button::touch(touch_event event)
    {
        rect_item::touch(event);


        auto orgx = static_cast<float>(event.xpos) 
                  / get_width() + 0.5f;

        auto orgy = -static_cast<float>(event.ypos) 
                  / get_height() + 0.5f;


        switch (event.type)
        {
            case touch_event::press:
            {
                glm::vec4 shadow(0.0f, 0.0f, orgx, orgy);

                shadows.insert(shadows.begin(), shadow);
                break;
            }

            case touch_event::move:
                if (is_pressed() and not shadows.empty())
                {
                    shadows.front()[2] = orgx;
                    shadows.front()[3] = orgy;
                }
                break;

            default:
                break;
        }
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
