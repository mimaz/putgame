/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/math>

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
        get<world::way_path>()->reset();
        get<world::way_path>()->update();

        get<world::camera>()->move(glm::vec3(0, 0, -5));

        auto genbox = [this, ctx](int boxid) -> void {
            auto box = create_object<world::light_box>(ctx, boxid);

            std::uniform_real_distribution<float> angledist
                (0, math::pi * 2);

            auto angle = angledist(random_engine());
            auto xoff = cosf(angle);
            auto yoff = sinf(angle);

            box->translate(glm::vec3(xoff, yoff, 0) * 0.75f);
        };

        auto boxid0 = get<world::camera>()->get_frame_id() + 40;
        auto boxid1 = boxid0 + 30;

        genbox(boxid0);
        genbox(boxid1);
    }

    play_activity::~play_activity()
    {}

    void play_activity::on_shift(float x, float y)
    {
        get_player()->shift(x, y);
    }

    void play_activity::on_draw()
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
    }
}
