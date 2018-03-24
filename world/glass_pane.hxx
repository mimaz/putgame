/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_glass_pane_hxx
#define __world_glass_pane_hxx

#include <putgame/common>

#include "visible_object.hxx"

namespace world
{
    class glass_pane : public visible_object
    {
    public:
        glass_pane(context *ctx, 
                   common::rgb_color color, 
                   glm::vec2 size);

        ~glass_pane();

        common::rgb_color get_color() const { return color; }
        glm::vec2 get_size() const { return size; }

        glm::mat4 get_piece_matrix() const;

    private:
        common::rgb_color color;
        glm::vec2 size;
        glm::mat4 piece_matrix;
    };
}

#endif
