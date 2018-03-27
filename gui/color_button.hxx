/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __gui_color_button_hxx
#define __gui_color_button_hxx

#include <putgame/text>

#include "rect_item.hxx"

namespace gui
{
    class color_button : public rect_item
    {
    public:
        color_button(common::context *ctx);

        void set_back_normal_color(glm::vec4 color);
        void set_back_highlight_color(glm::vec4 color);
        void set_text_normal_color(glm::vec4 color);
        void set_text_highlight_color(glm::vec4 color);

        void draw() override;
        void bind_texture();

        glm::vec4 get_back_normal_color() const
        { return back_normal_color; }

        glm::vec4 get_back_highlight_color() const
        { return back_highlight_color; }

        glm::vec4 get_text_normal_color() const
        { return text_normal_color; }

        glm::vec4 get_text_highlight_color() const
        { return text_highlight_color; }

    protected:
        void on_size_changed() override;

    private:
        glm::vec4 back_normal_color;
        glm::vec4 back_highlight_color;
        glm::vec4 text_normal_color;
        glm::vec4 text_highlight_color;

        text::text_buffer text;
    };
}

#endif
