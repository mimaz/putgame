/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "play_activity.hxx"

namespace game
{
    play_activity::play_activity(common::context *ctx)
        : object(ctx)
    {
        auto way = get_part<world::way_path>();

        way->reset();
        way->update();

        auto box = std::make_shared<world::light_box>
            (ctx, 130, world::light_box::white);

        box->translate(glm::vec3(0.8, 0, 0));

        register_object(box);
    }

    play_activity::~play_activity()
    {
    }

    void play_activity::on_draw()
    {
    }

    void play_activity::register_object(object_ref ref)
    {
        object_set.insert(ref);
    }

    void play_activity::delete_unreachable_objects()
    {

    }

    void play_activity::delete_all_objects()
    {
        object_set.clear();
    }
}
