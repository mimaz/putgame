/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "light_box_manager.hxx"

#include "light_box.hxx"
#include "light_box_view.hxx"

namespace world
{
    light_box_manager::light_box_manager(context *ctx)
        : object_manager(ctx)
        , light_range(20)
    {}

    void light_box_manager::set_light_range(float range)
    {
        light_range = range;
    }

    void light_box_manager::on_draw(light_box *box)
    {
        box->rotate();
    }

    light_box_view *light_box_manager::new_view()
    {
        return new light_box_view(get_context());
    }
}
