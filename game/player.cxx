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
        else if (test_collision())
        {
            auto cam = get<world::camera>();
            auto way = get<world::way_path>();

            auto camid = cam->get_frame_id();
            auto camframe = way->at(camid);

            auto radius = camframe.position() - cam->get_position();
            auto camoff = radius * 0.05f;

            cam->move(camoff);



            auto norm = camframe.position() - cam->get_position();
            
            auto vect = -cam->get_direction();
            auto axis = glm::normalize(glm::cross(norm, vect));

            auto cosine = glm::dot(vect, norm);
            auto angle = math::pi - 2 * acosf(cosine);

            cam->rotate(angle, axis);
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
