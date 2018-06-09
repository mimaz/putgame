/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/common>
#include <putgame/math>

#include "way_path.hxx"

#include "camera.hxx"
#include "constants.hxx"

namespace world
{
    const float way_path::gap = way_frame_gap;

    way_path::way_path(common::context *ctx)
        : path_line(ctx, gap)
        , generator(std::bind(&way_path::default_generator, this))
    {
        reset();
    }

    void way_path::set_generator(segment_gen gen)
    {
        generator = gen;
    }

    void way_path::generate_back()
    {
        if (seg == nullptr or seg->count < 1)
            seg = generator();

        seg->count--;

        append(seg->angle, seg->axis);
    }

    void way_path::reset()
    {
        path_line::reset(glm::mat4(1));
    }

    void way_path::update()
    {
        auto camid = get<camera>()->get_frame_id();
        auto range = get<camera>()->get_view_range();
        auto frame_range = static_cast<int>(range / get_gap());

        auto head_too_close = [this, camid, frame_range]() -> bool {
            try {
                return back().index() - camid < frame_range;
            } catch (no_point) {
                return true;
            }
        };

        auto tail_too_far = [this, camid, frame_range]() -> bool {
            try {
                return camid - front().index() > frame_range;
            } catch (no_point) {
                return false;
            }
        };

        while (head_too_close())
            generate_back();

        while (tail_too_far())
            remove_front();
    }

    way_path::segment_ref way_path::default_generator()
    {
        return std::make_shared<way_path::segment>
            (20, 0.0f, glm::vec3(0, 1, 0));
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
