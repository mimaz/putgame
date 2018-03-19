/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "light_box_manager.hxx"
#include "light_box_view.hxx"
#include "light_box.hxx"

namespace world
{
    light_box_manager::light_box_manager(context *ctx)
        : context_part(ctx)
        , view(std::make_shared<light_box_view>(ctx))
        , stripped(false)
        , light_range(20)
    {}

    void light_box_manager::register_box(light_box *box)
    {
        boxes.insert(box);
    }

    void light_box_manager::unregister_box(light_box *box)
    {
        boxes.erase(box);
    }

    void light_box_manager::set_stripped(bool strip)
    {
        stripped = strip;
    }

    void light_box_manager::set_light_range(float range)
    {
        light_range = range;
    }

    void light_box_manager::draw_all()
    {
        get_view()->begin_drawing(is_stripped());

        for (auto box : boxes)
        {
            box->on_draw();

            get_view()->draw(box);
        }

        get_view()->end_drawing();
    }
}
