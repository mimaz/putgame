/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */


#include "color_button.hxx"

#include "color_button_view.hxx"
#include "surface.hxx"

namespace gui
{
    color_button::color_button(common::context *ctx,
                               property_handler handler)
        : rect_item(ctx)
        , text(ctx, get<surface>()->get_font_builder())
        , handler(handler)
    {
        set_primary_color(glm::vec4(1.0f, 1.0f, 0.5f, 0.4f));
        set_secondary_color(glm::vec4(0.4f, 0.4f, 0.4f, 0.2));
    }

    void color_button::set_text(const std::string &txt)
    {
        text.set_text(txt);
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

        get<color_button_view>()->draw(this);
    }

    void color_button::process()
    {
        rect_item::process();

        constexpr auto show_speed = 0.15f;
        constexpr auto hide_speed = 0.175f;

        auto count = static_cast<int>(shadows.size());

        for (auto i = 0; i < count; i++)
        {
            shadows[i][0] += show_speed;

            if (i > 0 or not is_pressed())
                shadows[i][1] += hide_speed;
        }


        auto newend = std::remove_if(shadows.begin(), shadows.end(),
                [this](const glm::vec4 &v) -> bool {
                    return v[1] > sqrtf(2) * get_width() / get_height();
                });

        auto newsiz = std::distance(shadows.begin(), newend);

        shadows.resize(newsiz);
    }

    void color_button::touch(touch_event event)
    {
        rect_item::touch(event);


        auto normalize = [](float pos, float dim) -> float {
            pos = std::min(dim / 2, pos);
            pos = std::max(-dim / 2, pos);

            return pos / dim + 0.5f;
        };

        auto orgx = normalize(event.xpos, get_width());
        auto orgy = normalize(event.ypos, get_height());

        auto inside = event.xpos >= -get_width() / 2 and
            event.xpos <= get_width() / 2 and
            event.ypos >= -get_height() / 2 and
            event.ypos <= get_height();

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

            case touch_event::release:
                if (inside)
                    handler(this);
                break;

            default:
                break;
        }
    }

    void color_button::bind_texture()
    {
        glBindTexture(GL_TEXTURE_2D, text.get_texture_handle());
    }

    std::string color_button::get_text() const
    {
        return text.get_text();
    }

    void color_button::on_size_changed()
    {
        rect_item::on_size_changed();

        common::logd("setting text size: ", get_width(), ":", get_height());

        text.set_size(get_width(), get_height());
        text.set_font_size(get_height() / 4);
    }
}
