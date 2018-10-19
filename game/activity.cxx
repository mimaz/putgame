/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/math>

#include "activity.hxx"

#include "player.hxx"
#include "hit_mask.hxx"
#include "main_menu.hxx"

namespace game
{
    activity::activity(common::context *ctx)
        : object(ctx)
        , last_way_id(-1)
        , last_distance(-1)
        , last_difficulty(-1)
        , stat(splash)
        , transiting(false)
    {
        auto tgen = get<tunnel_generator>();
        auto waygen = std::bind(&tunnel_generator::generate, tgen);

        get<player>()->set_autopilot(true);

        get<world::way_path>()->set_generator(waygen);
        get<world::way_path>()->reset();

        switch_state(menu);
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

            get<object_generator>()->generate();
        }


        get_player()->process();

        if (is_transiting())
        {
            switch (get_state())
            {
            case menu:
                transiting = get<main_menu>()->is_animating();
                break;

            default:
                break;
            }
        }
        else
        {
        }
    }

    void activity::switch_state(state st)
    {
        if (st != stat)
        {
            if (transiting)
            {
                common::loge("cannot set state while transiting!");
                get_context()->exit();
            }

            transiting = true;

            switch (st)
            {
            case menu:
                get<main_menu>()->enable();
                break;

            case play:
                get<main_menu>()->disable();
                get<player>()->set_autopilot(false);
                break;

            case defeated:
                common::logi("DEFEATED");
                break;

            default:
                break;
            }

            stat = st;
        }
    }

    activity::state activity::get_state() const
    {
        return stat;
    }

    bool activity::is_transiting() const
    {
        return transiting;
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
        return get<player>();
    }

    hit_mask *activity::get_hit_mask()
    {
        return get<hit_mask>();
    }

    void activity::break_pane(world::glass_pane *pane)
    {
        common::logd("break_pane");
    }
}
