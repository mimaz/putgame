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
        void preprocess() override;
        void bind_texture();

        glm::vec4 get_back_normal_color() const;
        glm::vec4 get_back_highlight_color() const;
        glm::vec4 get_text_normal_color() const;
        glm::vec4 get_text_highlight_color() const;

        const std::array<glm::vec4, 4> &get_color_array() const
        { return colors; }

        const std::vector<glm::vec4> &get_shadows() const 
        { return shadows; }

    protected:
        void on_size_changed() override;

    private:
        std::array<glm::vec4, 4> colors;

        text::text_buffer text;

        std::vector<glm::vec4> shadows;
    };
}

#endif
