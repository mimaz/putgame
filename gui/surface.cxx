/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "surface.hxx"

namespace gui
{
    surface::surface(common::context *ctx)
        : part(ctx)
        , dirty_proj(true)
        , width(2)
        , height(2)
        , font_builder(text::default_font)
    {}

    void surface::resize(int w, int h)
    {
        width = w;
        height = h;
        dirty_proj = true;
    }

    glm::mat4 surface::get_proj() const
    {
        if (dirty_proj)
        {
            dirty_proj = false;

            auto w = get_width() / 2.0f;
            auto h = get_height() / 2.0f;

            proj = glm::ortho(-w, w, -h, h);
        }

        return proj;
    }
}
