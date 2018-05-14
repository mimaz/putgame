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
        , camera_frame(0)
    {}

    void way_path::set_generator(segment_gen gen)
    {
        generator = gen;
    }

    void way_path::camera_moved()
    {
        dirty_camera_frame = true;
    }

    void way_path::update()
    {
        auto camid = get_camera_frame();
        auto range = get_part<camera>()->get_view_range() * 2;
        auto range_gap = static_cast<int>(range) / get_gap();

        auto head_too_close = [=]() -> bool {
            auto headidx = get_last_point().get_index();

            return headidx - camid < range_gap;
        };

        while (head_too_close())
            generate_frame();
    }

    int way_path::get_camera_frame()
    {
        if (dirty_camera_frame)
        {
            dirty_camera_frame = false;

            update_camera_frame();
        }

        return camera_frame;
    }

    void way_path::generate_frame()
    {
        if (seg == nullptr or seg->count < 1)
            seg = generator();

        seg->count--;

        append(seg->angle, seg->axis);
    }

    void way_path::update_camera_frame()
    {
        auto campos = get_part<camera>()->get_position();

        auto cam_sqdist = [this, campos](int idx) -> float {
            auto frpos = get_point(idx).get_position();

            return math::sqdist(campos, frpos);
        };


        while (get_first_point().get_index() < camera_frame
                and cam_sqdist(camera_frame - 1)
                < cam_sqdist(camera_frame))
        {
            camera_frame--;
        }

        while (get_last_point().get_index() > camera_frame
                and cam_sqdist(camera_frame + 1)
                < cam_sqdist(camera_frame))
        {
            camera_frame++;
        }
    }

    way_path::segment_ref way_path::default_generator()
    {
        std::uniform_real_distribution<float> dist(20, 40);

        auto angle = dist(random_engine());

        return std::make_shared<way_path::segment>
            (angle, math::pi / 2, glm::vec3(0, 1, 0));
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
