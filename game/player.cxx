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
    class player::axis_correction : common::context::object
    {
    public:
        axis_correction(player *pl, glm::vec3 ax)
            : object(pl)
            , axis(ax)
            , momentum(0)
        {}

        void correct()
        {
            auto tframe = get<world::way_path>()
                ->get_camera_frame() + 50;
            auto tmatrix = get<world::way_path>()
                ->point(tframe).get_matrix();
            auto target = math::coord3d(tmatrix)
                - get<world::camera>()->get_position();

            auto gradient_step = math::pi / 60;
            auto gradient = get<world::camera>()
                ->gradient(gradient_step, axis, target);

            if (gradient != gradient) 
                return;

            momentum = 0.96f * momentum + 0.04f * gradient;

            get<world::camera>()
                ->rotate(math::pi * momentum, axis);
        }

        glm::vec3 axis;
        float momentum;
    };

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
        get<world::camera>()->move(glm::vec3(0, 0, -0.05));

        if (apilot != nullptr)
            apilot->correct();
    }

    int player::get_frame_id()
    {
        return get<world::way_path>()->get_camera_frame();
    }
}
