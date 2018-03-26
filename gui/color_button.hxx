/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __gui_color_button_hxx
#define __gui_color_button_hxx

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

        glm::vec4 get_back_normal_color() const
        { return back_normal_color; }

        glm::vec4 get_back_highlight_color() const
        { return back_highlight_color; }

        glm::vec4 get_text_normal_color() const
        { return text_normal_color; }

        glm::vec4 get_text_highlight_color() const
        { return text_highlight_color; }

    private:
        glm::vec4 back_normal_color;
        glm::vec4 back_highlight_color;
        glm::vec4 text_normal_color;
        glm::vec4 text_highlight_color;
    };
}

#endif
