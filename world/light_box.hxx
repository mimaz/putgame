/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_light_box_hxx
#define __world_light_box_hxx

#include <putgame/common>

#include "visible_object.hxx"
#include "light_source.hxx"

namespace world
{
    class light_box_manager;

    class light_box : public visible_object, public light_source
    {
    public:
        enum color
        {
            red,
            green,
            blue,
        };

        light_box(context *ctx, color col);
        ~light_box();

        void rotate();
        void rotate(float angle);

        void set_color(color col);
        void set_speed(float speed);

        color get_color() const { return col; }
        float get_speed() const { return speed; }

        common::rgb_color get_surface_color() const;

        glm::vec3 get_light_position() override;
        glm::vec3 get_light_color() override;
        float get_light_range() override;

    private:
        color col;
        common::rgb_color light_col;
        common::rgb_color surface_col;

        float speed;
        float blur;
    };
}

#endif
