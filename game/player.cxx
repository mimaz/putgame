/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/world>
#include <putgame/math>

#include "player.hxx"

#include "play_activity.hxx"

namespace game
{
    player::player(play_activity *activity)
        : object(activity->get_context())
        , activity(activity)
        , momentum(0)
        , autopilot(false)
    {
        get_part<world::camera>()->rotate(-math::pi / 8, glm::vec3(0, 1, 0));
    }

    void player::set_autopilot(bool ap)
    {
        autopilot = ap;
    }

    void player::on_draw()
    {
        get_part<world::camera>()->move(glm::vec3(0, 0, -0.02));

        if (autopilot)
            correct_direction();
    }

    int player::get_frame_id()
    {
        return get_part<world::way_path>()->get_camera_frame();
    }

    void player::correct_direction()
    {
        auto target_frame = get_frame_id() + 50;
        auto target_matrix = get_part<world::way_path>()
            ->point(target_frame).get_matrix();
        auto target = math::coord3d(target_matrix)
            - get_part<world::camera>()->get_position();

        auto gr = get_part<world::camera>()->gradient
            (math::pi / 60, glm::vec3(0, 1, 0), target);

        if (gr != gr)
            return;

        momentum *= 0.96f;
        momentum += gr * 0.04f;

        std::cout << "target: " << target 
            << ", gradient: " << gr 
            << ", position: " << get_part<world::camera>()->get_position()
            << std::endl;

        get_part<world::camera>()->rotate
            (math::pi * momentum, glm::vec3(0, 1, 0));
    }
}
