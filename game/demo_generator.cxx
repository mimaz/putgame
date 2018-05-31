/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/math>
#include <putgame/world>

#include "demo_generator.hxx"

#include "play_activity.hxx"

namespace game
{
    demo_generator::demo_generator(play_activity *act)
        : object_generator(act)
    {}

    void demo_generator::generate()
    {
        auto dist = std::normal_distribution<float>
            (0.0f, 1.0f)(random_engine());

        auto absdist = std::abs(dist);

        auto id = get<world::way_path>()->back().index();

        if (absdist > 2.65f)
        {
            common::logd("create glass");

            auto ptr = activity->create_object<world::glass_pane>
                (get_context(), id, glm::vec3(0.5f, 0.5f, 1.0f));
        }
        else if (absdist > 2.45f)
        {
            common::logd("create lightbox");

            std::uniform_real_distribution<float> angledist
                (0, math::pi * 2);

            auto ptr = activity->create_object<world::light_box>
                (get_context(), id);


            auto angle = angledist(random_engine());
            auto xoff = cosf(angle);
            auto yoff = sinf(angle);

            ptr->translate(glm::vec3(xoff, yoff, 0) / 2.0f);
        }

        object_generator::generate();
    }
}
