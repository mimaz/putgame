/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "play_activity.hxx"

#include "player.hxx"

namespace game
{
    play_activity::play_activity(common::context *ctx)
        : object(ctx)
        , player(std::make_shared<game::player>(this))
    {
        auto way = get<world::way_path>();

        way->reset();
        way->update();

        auto box = create_object<world::light_box>
            (ctx, 130, world::light_box::white);

        box->translate(glm::vec3(0.8, 0, 0));

        player->set_autopilot(true);
    }

    play_activity::~play_activity()
    {
    }

    void play_activity::on_draw()
    {
        auto camid = get<world::way_path>()->get_camera_frame();

        while (not object_queue.empty() 
                and object_queue.front()->get_frame_id() < camid)
        {
            object_queue.pop_front();

            std::cout << "delete first object" << std::endl;
        }

        get_player()->on_draw();
    }
}
