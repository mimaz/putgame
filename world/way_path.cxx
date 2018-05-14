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
    namespace
    {
        way_path::segment_ref default_gen()
        {
            return std::make_shared<way_path::segment>
                (10, 0, glm::vec3(0, 1, 0));
        }
    }

    way_path::way_path(common::context *ctx)
        : path_line(ctx, way_frame_gap)
        , generator(default_gen)
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
}
