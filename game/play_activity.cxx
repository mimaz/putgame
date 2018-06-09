/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/math>

#include "play_activity.hxx"

#include "player.hxx"
#include "hit_mask.hxx"

namespace game
{
    play_activity::play_activity(common::context *ctx)
        : object(ctx)
        , player_obj(this)
        , object_generator_obj(this)
        , hit_mask_obj(this)
        , last_way_id(-1)
    {
        get<world::way_path>()->reset();
        get<world::way_path>()->update();
    }

    void play_activity::steer(float x, float y)
    {
        get_player()->steer(x, y);
    }

    void play_activity::process()
    {
        auto camid = get<world::camera>()->get_frame_id();

        while (not object_queue.empty() 
                and object_queue.front()->get_frame_id() < camid)
        {
            auto item = object_queue.front().get();
            auto pane = dynamic_cast<world::glass_pane *>(item);

            if (pane != nullptr)
                break_pane(pane);

            common::logd("delete last object");

            object_queue.pop_front();
        }



        if (get<world::way_path>()->back().index() != last_way_id)
        {
            last_way_id = get<world::way_path>()->back().index();

            get_object_generator()->generate();
        }


        get_player()->process();
        get_hit_mask()->process();

        common::logd("distance: ", get_distance());
    }

    int play_activity::get_distance()
    {
        return get_player()->get_frame_id();
    }

    void play_activity::break_pane(world::glass_pane *pane)
    {
        common::logd("break_pane");
    }
}
