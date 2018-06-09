/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/math>

#include "object_generator.hxx"

#include "play_activity.hxx"

namespace game
{
    object_generator::object_generator(play_activity *act)
        : object(act)
        , activity(act)
    {}

    void object_generator::generate()
    {
        auto dist = std::normal_distribution<float>
            (0.0f, 1.0f)(random_engine());

        auto absdist = std::abs(dist);

        auto id = get<world::way_path>()->back().index();

        std::uniform_real_distribution<float> angledist
            (0, math::pi * 2);

        auto angle = angledist(random_engine());
        auto xoff = cosf(angle);
        auto yoff = sinf(angle);
        auto offvec = glm::vec3(xoff, yoff, 0.0f) * 0.75f;


        if (absdist > 2.8f)
        {
            common::logd("create wall obstacle");

            auto ptr = activity->create_object<world::wall_obstacle>
                (get_context(), id, 6, 4);

            ptr->translate(offvec);
        }
        else if (absdist > 2.65f)
        {
            common::logd("create glass");

            activity->create_object<world::glass_pane>
                (get_context(), id, glm::vec3(0.5f, 0.5f, 1.0f));
        }
        else if (absdist > 2.45f)
        {
            common::logd("create lightbox");

            auto ptr = activity->create_object<world::light_box>
                (get_context(), id);


            ptr->translate(offvec);
        }
    }
}
