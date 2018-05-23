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
        using handler_type = std::function<void(color_button *)>;

        color_button(common::context *ctx, 
                     handler_type handler);

        void set_text(const std::string &text);
        void set_primary_color(glm::vec4 color);
        void set_secondary_color(glm::vec4 color);

        void draw() override;
        void process() override;
        void touch(touch_event event) override;

        void bind_texture();

        std::string get_text() const;

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
