/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/world>
#include <putgame/math>

#include "player.hxx"

#include "autopilot.hxx"
#include "play_activity.hxx"

namespace game
{
    player::player(play_activity *activity)
        : object(activity->get_context())
        , apilot(nullptr)
        , activity(activity)
    {}

    void player::shift(float x, float y)
    {
        glm::vec3 axisx(0, 1, 0);
        glm::vec3 axisy(-1, 0, 0);

        auto factor = math::pi / 3;

        get<world::camera>()->rotate(x * factor, axisx);
        get<world::camera>()->rotate(y * factor, axisy);
    }

    void player::process()
    {
        if (apilot != nullptr)
        {
            apilot->correct();
        }
        else
        {
            try {
                test_collision();
            } catch (glm::vec3 point) {
                auto offs = point - get<world::camera>()->get_position();

                get<world::camera>()->move(offs);
                common::logd("ouch");
            }
        }
    }

    void player::set_autopilot(bool ap)
    {
        if (ap)
            apilot = std::make_shared<autopilot>(this);
        else
            apilot = nullptr;
    }

    int player::get_frame_id()
    {
        return get<world::camera>()->get_frame_id();
    }

    void player::test_collision()
    {
        auto eye = get<world::camera>()->get_position();
        auto fid = get<world::camera>()->get_frame_id();
        auto fra = get<world::way_path>()->at(fid);
        auto center = math::coord3d(fra);

        auto sqd = math::sqdist(center, eye);

        if (sqd > 1)
            throw center + glm::normalize(eye - center) * 0.8f;
    }
}
