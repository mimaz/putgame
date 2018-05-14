/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "play_stage.hxx"
#include "main_menu.hxx"

namespace game
{
    play_stage::play_stage(common::context *ctx)
        : object(ctx)
    {
        menu_ptr = std::make_shared<main_menu>(ctx);

        return;
        auto box = std::make_shared<world::light_box>
            (ctx, 0, world::light_box::white);

        box->translate(glm::vec3(0.5, 0, 0));

        register_object(box);
    }

    play_stage::~play_stage()
    {
    }

    void play_stage::on_draw()
    {
    }

    void play_stage::register_object(object_ref ref)
    {
        object_set.insert(ref);
    }

    void play_stage::delete_unreachable_objects()
    {

    }

    void play_stage::delete_all_objects()
    {
        object_set.clear();
    }
}
