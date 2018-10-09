/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/math>
#include <putgame/world>

#include "player.hxx"

#include "autopilot.hxx"
#include "activity.hxx"
#include "hit_mask.hxx"

namespace game
{
    player::player(common::context *ctx)
        : object(ctx)
        , apilot(std::make_shared<autopilot>(this))
        , apilot_enabled(false)
        , target_speed(10)
        , real_speed(0)
    {}

    void player::steer(float x, float y)
    {
        glm::vec3 axisx(0, 1, 0);
        glm::vec3 axisy(-1, 0, 0);

        auto factor = math::pi / 3;

        get<world::camera>()->rotate(x * factor, axisx);
        get<world::camera>()->rotate(y * factor, axisy);
    }

    void player::process()
    {
        auto fps = std::get<int>(get_property("fps"));
        auto factor = 1.0f / fps;

        auto cam = get<world::camera>();


        real_speed += (get_target_speed() - get_real_speed()) * factor;

        glm::vec3 movec(0, 0, -get_real_speed() / fps);

        cam->move(movec);


        if (apilot_enabled)
        {
            apilot->correct();
        }
        else if (test_collision())
        {
            auto hmask = get<hit_mask>();

            apilot->correct(0.5f);
            hmask->hit(0.1f);

            if (hmask->get_exposure() > 1)
                get<activity>()->switch_state(activity::defeated);
        } 
        else 
        {
            apilot->reset();
        }
    }

    void player::set_autopilot(bool ap)
    {
        apilot_enabled = ap;
    }

    int player::get_frame_id() const
    {
        return get<world::camera>()->get_frame_id();
    }

    float player::get_target_speed() const
    {
        return target_speed;
    }

    float player::get_real_speed() const
    {
        return real_speed;
    }

    bool player::test_collision()
    {
        auto eye = get<world::camera>()->get_position();
        auto fid = get<world::camera>()->get_frame_id();
        auto fra = get<world::way_path>()->at(fid);
        auto center = math::coord3d(fra);

        auto sqd = math::sqdist(center, eye);

        return sqd >= 1;
    }
}
