/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/math>
#include <putgame/world>

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
        get<world::camera>()->move(glm::vec3(0, 0, -0.1f));

        if (apilot != nullptr)
        {
            apilot->correct();
        }
        else
        {
            try {
                test_collision();
            } catch (glm::vec3 point) {
                // TODO make an offset

                auto cam = get<world::camera>();
                auto camid = cam->get_frame_id();
                auto camframe = get<world::way_path>()->at(camid);

                auto norm = camframe.position() - cam->get_position();
                
                auto vect = -get<world::camera>()->get_direction();
                auto axis = glm::normalize(glm::cross(norm, vect));

                auto cosine = glm::dot(vect, norm);
                auto angle = math::pi - 2 * acosf(cosine);

                get<world::camera>()->rotate(angle, axis);
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
