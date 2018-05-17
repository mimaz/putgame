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
        , autopilot(false)
        , momentum(0)
    {
        get_part<world::camera>()->rotate(-math::pi / 8, glm::vec3(0, 1, 0));
    }

    void player::set_autopilot(bool ap)
    {
        autopilot = ap;
    }

    void player::on_draw()
    {
        get_part<world::camera>()->move(glm::vec3(0, 0, -0.01));

        if (autopilot)
        {
            auto target_frame = get_frame_id() + 10;
            auto target_matrix = get_part<world::way_path>
                ()->point(target_frame).get_matrix();

            auto target = math::coord3d(target_matrix);

            correct_direction(target);
        }
    }

    int player::get_frame_id()
    {
        return get_part<world::way_path>()->get_camera_frame();
    }

    void player::correct_direction(glm::vec3 target)
    {
        auto vector = target - get_part<world::camera>()->get_position();
        auto direction = get_part<world::camera>()->get_direction();

        auto angle = acosf(glm::dot(direction, vector));
        auto cross = glm::cross(direction, vector);

        get_part<world::camera>()->rotate(angle / 60, cross);

        std::cout 
            << "angle: " << angle / 60
            << ", cross: " << cross 
            << std::endl;
        /*
            << ", target: " << target 
            << ", direction: " << direction 
            */
    }
}
