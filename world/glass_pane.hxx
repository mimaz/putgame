/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_glass_pane_hxx
#define __world_glass_pane_hxx

#include <common/rgb_color.hxx>

#include "visible_object.hxx"

namespace world
{
    class glass_pane : public visible_object
    {
    public:
        glass_pane(context *ctx, 
                   common::rgb_color color, 
                   glm::vec2 size);

        common::rgb_color get_color() const { return color; }
        glm::vec2 get_size() const { return size; }

    private:
        common::rgb_color color;
        glm::vec2 size;
    };
}

#endif
