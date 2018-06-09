/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include "color_rectangle.hxx"

#include "color_rectangle_view.hxx"

namespace gui
{
    color_rectangle::color_rectangle(common::context *ctx, 
                                     int depth)
        : rect_item(ctx)
        , color(glm::vec4(0, 0, 0, 1))
    {}

    void color_rectangle::set_color(glm::vec4 col)
    {
        color = col;
    }

    void color_rectangle::draw()
    {
        rect_item::draw();

        get<color_rectangle_view>()->draw(this);
    }
}
