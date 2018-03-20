/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_glass_piece_hxx
#define __world_glass_piece_hxx

#include <common/rgb_color.hxx>

#include "visible_object.hxx"

namespace world
{
    class glass_pane;

    class glass_piece : public visible_object
    {
    public:
        glass_piece(glass_pane *pane);

        ~glass_piece();

        void on_draw();

        common::rgb_color get_color() const { return color; }

    private:
        common::rgb_color color;

        float rotation_speed;
        glm::vec3 rotation_axis;
    };
}

#endif
