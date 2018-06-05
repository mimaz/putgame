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
            color_count
        };

        light_box(common::context *ctx, int frameid);
        light_box(common::context *ctx, int frameid, color col);
        ~light_box();

        void process();

        void set_color(color col);

        color get_color() const { return col; }

        glm::vec3 get_surface_color() const;

        glm::vec3 get_light_position() override;
        glm::vec3 get_light_color() override;
        float get_light_range() override;

    private:
        float rand_speed();

        color col;
        glm::vec3 light_col;
        glm::vec3 surface_col;

        float speedx;
        float speedy;
        float speedz;
        float blur;
    };
}

#endif
