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

    void demo_generator::on_draw()
    {
        auto dist = std::normal_distribution<float>
            (0.0f, 1.0f)(random_engine());

        auto absdist = std::abs(dist);

        if (absdist > 2.75f)
        {
            std::cout << "create lightbox" << std::endl;

            std::uniform_real_distribution<float> angledist(0, math::pi * 2);


            auto id = get<world::way_path>()->last_index();
            auto ptr = activity->create_object<world::light_box>
                (get_context(), id);


            auto angle = angledist(random_engine());
            auto xoff = cosf(angle);
            auto yoff = sinf(angle);

            ptr->translate(glm::vec3(xoff, yoff, 0) / 2.0f);


            std::cout << ptr->get_frame_id()
                      << " cam " 
                      << get<world::camera>()->get_frame_id() 
                      << std::endl;
        }

        object_generator::on_draw();
    }
}
