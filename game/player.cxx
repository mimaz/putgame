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
    player::player(activity *act)
        : object(act->get_context())
        , act(act)
        , apilot(nullptr)
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
        constexpr auto fps = 40;
        constexpr auto factor = 1.0f / fps;

        auto cam = get<world::camera>();


        real_speed += (get_target_speed() - get_real_speed()) * factor;


        glm::vec3 movec(0, 0, -get_real_speed() / fps);

        cam->move(movec);



        if (apilot != nullptr)
        {
            apilot->correct();
        }
        else if (test_collision())
        {
            auto way = get<world::way_path>();

            auto camid = cam->get_frame_id();
            auto camframe = way->at(camid);

            auto radius = camframe.position() - cam->get_position();
            auto camoff = radius * 0.1f;

            cam->move(camoff);



            auto norm = camframe.position() - cam->get_position();
            
            auto vect = -cam->get_direction();
            auto axis = glm::normalize(glm::cross(norm, vect));

            auto cosine = glm::dot(vect, norm);
            auto angle = math::pi - 2 * acosf(cosine);

            cam->rotate(angle, axis);

            common::logd("cos: ", cosine);


            act->get_hit_mask()->hit(cosine);
        }
    }

    void player::set_autopilot(bool ap)
    {
        if (ap)
            apilot = std::make_shared<autopilot>(this);
        else
            apilot = nullptr;
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
