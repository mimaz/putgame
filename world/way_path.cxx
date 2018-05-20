/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>
#include <putgame/math>

#include "way_path.hxx"

#include "camera.hxx"
#include "constants.hxx"

namespace world
{
    way_path::way_path(common::context *ctx)
        : path_line(ctx, way_frame_gap)
        , generator(std::bind(&way_path::default_generator, this))
    {}

    void way_path::set_generator(segment_gen gen)
    {
        generator = gen;
    }

    void way_path::reset()
    {
        path_line::reset_matrix(glm::mat4(1));
    }

    void way_path::update()
    {
        auto campos = get<camera>()->get_position();
        auto range = get<camera>()->get_view_range() * 2;
        auto sqrange = range * range;

        auto head_too_close = [campos, sqrange, this]() -> bool {
            auto head = math::coord3d(last_point().get_matrix());

            return math::sqdist(head, campos) < sqrange;
        };

        auto tail_too_far = [campos, sqrange, this]() -> bool {
            auto tail = math::coord3d(first_point().get_matrix());

            return math::sqdist(tail, campos) > sqrange;
        };

        while (head_too_close())
            generate_back();

        while (tail_too_far())
            remove_front();
    }

    void way_path::generate_back()
    {
        if (seg == nullptr or seg->count < 1)
            seg = generator();

        seg->count--;

        append(seg->angle, seg->axis);
    }

    way_path::segment_ref way_path::default_generator()
    {
        static const glm::vec3 axes[] = {
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0),
            glm::vec3(-1, 0, 0),
            glm::vec3(0, -1, 0),
        };

        constexpr auto axis_count = sizeof(axes) / sizeof(glm::vec3);


        auto angle = std::uniform_real_distribution<float>
            (math::pi / 4, math::pi / 2)(random_engine());

        auto axisid = std::uniform_int_distribution<int>
            (0, axis_count - 1)(random_engine());

        auto axis = axes[axisid];


        return std::make_shared<way_path::segment>
            (8, angle, axis);
    }

    way_path::segment::segment()
        : segment(0, 0, glm::vec3(0, 1, 0))
    {}

    way_path::segment::segment(float length, 
                               float angle, 
                               glm::vec3 axis)
        : count(length / way_frame_gap)
        , angle(angle / count)
        , axis(axis)
    {}
}
