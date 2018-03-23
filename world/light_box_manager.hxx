/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_light_box_manager_hxx
#define __world_light_box_manager_hxx

#include "object_manager.hxx"

namespace world
{
    class light_box;
    class light_box_view;

    class light_box_manager 
    : public object_manager<light_box, light_box_view>
    {
    public:
        light_box_manager(context *ctx);

        void set_light_range(float range);

        float get_light_range() const { return light_range; }

    protected:
        void on_draw(light_box *box) final;

        light_box_view *new_view() final;

    private:
        float light_range;
    };
}

#endif

