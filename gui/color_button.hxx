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

        void set_primary_color(glm::vec4 color);
        void set_secondary_color(glm::vec4 color);

        void draw() override;
        void preprocess() override;
        void touch(touch_event event) override;

        void bind_texture();

        glm::vec4 get_back_normal_color() const;
        glm::vec4 get_back_highlight_color() const;
        glm::vec4 get_text_normal_color() const;
        glm::vec4 get_text_highlight_color() const;

        glm::vec4 get_primary_color() const
        { return primary_color; }

        glm::vec4 get_secondary_color() const
        { return secondary_color; }

        const std::vector<glm::vec4> &get_shadows() const 
        { return shadows; }

    protected:
        void on_size_changed() override;

    private:
        glm::vec4 primary_color;
        glm::vec4 secondary_color;

        text::text_buffer text;

        std::vector<glm::vec4> shadows;
    };
}

#endif
