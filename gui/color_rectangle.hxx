/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __gui_color_rectangle_hxx
#define __gui_color_rectangle_hxx

#include "rect_item.hxx"

namespace gui
{
    class color_rectangle : public rect_item
    {
    public:
        color_rectangle(common::context *ctx, 
                        int depth = 0);

        void set_color(glm::vec4 col);

        glm::vec4 get_color() const
        { return color; }

        void draw() override;

    private:
        glm::vec4 color;
    };
}

#endif
