/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>
#include <putgame/math>

#include "way_path.hxx"

#include "camera.hxx"

namespace world
{
    class way_path::segment
    {
    public:
        segment()
            : segment(0, 0, glm::vec3(0, 1, 0)) {}

        segment(int count, float angle, glm::vec3 axis)
            : count(count), angle(angle / count), axis(axis) {}

        int count;
        float angle;
        glm::vec3 axis;
    };

    way_path::way_path(common::context *ctx)
        : common::context::part(ctx)
        , path_line(0.05)
        , camera_frame(0)
    {
        for (int i = 0; i < 1000; i++)
            generate_back();
    }

    void way_path::generate_back()
    {
        if (back == nullptr or back->count < 1)
            back = generate();

        back->count--;

        append(back->angle, back->axis);
    }

    void way_path::update_camera_frame()
    {
        dirty_camera_frame = true;
    }

    int way_path::get_camera_frame()
    {
        if (dirty_camera_frame)
        {
            dirty_camera_frame = false;


            auto frpos = [this](int idx) -> glm::vec3 {
                return get_point(idx).get_position();
            };

            auto campos = get_part<camera>()->get_position();

            while (get_first_point().get_index() < camera_frame
                    and glm::distance(campos, frpos(camera_frame - 1))
                    < glm::distance(campos, frpos(camera_frame)))
            {
                camera_frame--;
            }

            while (get_last_point().get_index() > camera_frame
                    and glm::distance(campos, frpos(camera_frame + 1))
                    < glm::distance(campos, frpos(camera_frame)))
            {
                camera_frame++;
            }
        }

        return camera_frame;
    }

    way_path::segment_ptr way_path::generate() const
    {
        return std::make_shared<segment>
            (10, math::pi / 4000, glm::vec3(0, 1, 0));
    }
}
