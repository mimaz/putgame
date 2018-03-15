/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_light_box_hxx
#define __world_light_box_hxx

#include "visible_object.hxx"
#include "rgb_color.hxx"

namespace world
{
    class light_box : public visible_object
    {
    public:
        light_box(context *ctx, common::rgb_color color);

        void draw() override;

        void set_color(const common::rgb_color &color);
        void set_speed(float speed);

        common::rgb_color get_color() const { return color; }
        float get_speed() const { return speed; }
        float get_angle() const { return angle; }

    private:
        common::rgb_color color;

        float speed;
        float angle;
        float blur;
    };
}

#endif
