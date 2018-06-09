/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/math>

#include "activity.hxx"

#include "player.hxx"
#include "hit_mask.hxx"

namespace game
{
    activity::activity(common::context *ctx)
        : object(ctx)
        , play(this)
        , ogen(this)
        , tgen(this)
        , hmsk(this)
        , last_way_id(-1)
        , last_distance(-1)
        , last_difficulty(-1)
    {
        auto waygen = std::bind(&tunnel_generator::generate, get_tunnel_generator());

        get<world::way_path>()->set_generator(waygen);
        get<world::way_path>()->reset();
    }

    void activity::steer(float x, float y)
    {
        get_player()->steer(x, y);
    }

    void activity::process()
    {
        auto camid = get<world::camera>()->get_frame_id();

        while (not object_queue.empty() 
                and object_queue.front()->get_frame_id() < camid)
        {
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

        common::logd("difficulty: ", get_difficulty());
    }

    int activity::get_distance()
    {
        auto fid = get_player()->get_frame_id();

        return static_cast<int>(fid * world::way_path::gap);
    }

    int activity::get_difficulty()
    {
        auto dist = get_distance();

        if (dist != last_distance)
        {
            last_distance = dist;

            auto arg = std::max(dist, 0) + math::e * 10;
            auto dif = log(arg) * 100;

            last_difficulty = static_cast<int>(dif);
        }

        return last_difficulty;
    }

    player *activity::get_player()
    {
        return &play;
    }

    object_generator *activity::get_object_generator()
    {
        return &ogen;
    }

    tunnel_generator *activity::get_tunnel_generator()
    {
        return &tgen;
    }

    hit_mask *activity::get_hit_mask()
    {
        return &hmsk;
    }

    void activity::break_pane(world::glass_pane *pane)
    {
        common::logd("break_pane");
    }
}
