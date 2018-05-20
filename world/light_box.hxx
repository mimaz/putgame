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
            white,
            color_count
        };

        light_box(common::context *ctx, int frameid);
        light_box(common::context *ctx, int frameid, color col);
        ~light_box();

        void rotate();
        void rotate(float angle);

        void set_color(color col);
        void set_speed(float speed);

        color get_color() const { return col; }
        float get_speed() const { return speed; }

        glm::vec3 get_surface_color() const;

        glm::vec3 get_light_position() override;
        glm::vec3 get_light_color() override;
        float get_light_range() override;

    private:
        color col;
        glm::vec3 light_col;
        glm::vec3 surface_col;

        float speed;
        float blur;
    };
}

#endif
