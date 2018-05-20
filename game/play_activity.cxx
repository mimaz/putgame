/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "play_activity.hxx"

#include "player.hxx"
#include "demo_generator.hxx"

namespace game
{
    play_activity::play_activity(common::context *ctx)
        : object(ctx)
        , player_ref(std::make_shared<player>(this))
        , object_generator_ref(std::make_shared<demo_generator>(this))
        , last_way_id(-1)
    {
        auto way = get<world::way_path>();

        way->reset();
        way->update();

        get_player()->set_autopilot(true);
    }

    play_activity::~play_activity()
    {}

    void play_activity::on_draw()
    {
        auto camid = get<world::camera>()->get_frame_id();

        while (not object_queue.empty() 
                and object_queue.front()->get_frame_id() < camid)
        {
            std::cout << "delete last object" << std::endl;

            object_queue.pop_front();
        }



        if (get<world::way_path>()->last_index() != last_way_id)
        {
            last_way_id = get<world::way_path>()->last_index();

            get_object_generator()->generate();
        }


        get_player()->on_draw();
    }
}
