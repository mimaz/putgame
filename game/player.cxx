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
    {
        get<world::camera>()->rotate
            (-math::pi / 8, glm::vec3(0, 1, 0));
        get<world::camera>()->rotate
            (math::pi / 6, glm::vec3(1, 0, 0));
    }

    void player::set_autopilot(bool ap)
    {
        if (ap)
            apilot = std::make_shared<autopilot>(this);
        else
            apilot = nullptr;
    }

    void player::on_draw()
    {
        get<world::camera>()->move(glm::vec3(0, 0, -0.20));

        if (apilot != nullptr)
            apilot->correct();
    }

    int player::get_frame_id()
    {
        return get<world::camera>()->get_frame_id();
    }
}
