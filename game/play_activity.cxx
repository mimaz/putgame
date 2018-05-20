/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "play_activity.hxx"

#include "player.hxx"
#include "object_generator.hxx"

namespace game
{
    play_activity::play_activity(common::context *ctx)
        : object(ctx)
        , player_ref(std::make_shared<player>(this))
        , object_generator_ref(std::make_shared<object_generator>(this))
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
            object_queue.pop_front();

            std::cout << "delete first object" << std::endl;
        }

        get_player()->on_draw();
        get_object_generator()->on_draw();
    }
}
