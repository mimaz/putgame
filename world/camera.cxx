/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>
#include <putgame/math>

#include "camera.hxx"

#include "way_path.hxx"

enum
{
    dirty_proj = 0x01,
    dirty_view_proj = 0x02,
    dirty_inverse = 0x04,
    dirty_frame = 0x08,
    dirty_all = dirty_proj | dirty_view_proj | dirty_inverse | dirty_frame
};

constexpr auto near_plane = 0.01f;

namespace world
{
    camera::camera(common::context *ctx)
        : object(ctx)
        , light_source(ctx)
        , proj_mat(1)
        , view_mat(1)
        , flags(dirty_all)
        , view_angle(math::pi / 3)
        , view_ratio(1)
        , view_range(16)
    {}

    void camera::move(const glm::vec3 &vec)
    {
        flags |= dirty_frame;

        apply(glm::translate(-vec));
    }

    void camera::rotate(float angle, const glm::vec3 &axis)
    {
        apply(glm::rotate(-angle, axis));
    }

    void camera::apply(const glm::mat4 &matrix)
    {
        flags |= dirty_view_proj | dirty_inverse;

        view_mat = matrix * view_mat;
    }

    float camera::gradient(float angle, glm::vec3 axis, glm::vec3 targetvec)
    {
        auto newview = inversed_view() * glm::rotate(angle, axis);
        auto vector = math::direction3d(inversed_view());
        auto newvector = math::direction3d(newview);

        auto cosine = glm::dot(targetvec, vector);
        auto newcosine = glm::dot(targetvec, newvector);

        return (cosine - newcosine) / angle;
    }

    void camera::set_view_angle(float angle)
    {
        flags |= dirty_proj | dirty_view_proj;
        view_angle = angle;
    }

    void camera::set_view_ratio(float ratio)
    {
        flags |= dirty_proj | dirty_view_proj;
        view_ratio = ratio;
    }

    void camera::set_view_range(float range)
    {
        flags |= dirty_proj | dirty_view_proj;
        view_range = range;
    }

    const glm::mat4 &camera::get_proj()
    {
        if (flags & dirty_proj)
        {
            flags &= ~dirty_proj;

            proj_mat = glm::perspective(get_view_angle(), 
                                        get_view_ratio(),
                                        near_plane,
                                        get_view_range());
        }

        return proj_mat;
    }

    const glm::mat4 &camera::get_view()
    {
        return view_mat;
    }

    const glm::mat4 &camera::get_view_proj()
    {
        if (flags & dirty_view_proj)
        {
            flags &= ~dirty_view_proj;

            view_proj_mat = get_proj() * get_view();
        }

        return view_proj_mat;
    }

    glm::mat4 camera::make_mvp(const glm::mat4 &model)
    {
        return get_view_proj() * model;
    }

    glm::vec3 camera::get_position() 
    {
        return math::coord3d(inversed_view());
    }

    glm::vec3 camera::get_direction() 
    {
        return -math::direction3d(inversed_view());
    }

    glm::vec3 camera::get_top() 
    {
        return math::top3d(inversed_view());
    }

    glm::vec3 camera::get_light_position()
    {
        return get_position();
    }

    glm::vec3 camera::get_light_color()
    {
        return glm::vec3(1, 1, 1);
    }

    float camera::get_light_range()
    {
        return 150;
    }

    int camera::get_frame_id()
    {
        if (flags & dirty_frame)
        {
            update_frame_id();

            flags &= ~dirty_frame;
        }

        return frame_id;
    }

    glm::mat4 camera::inversed_view()
    {
        if (flags & dirty_inverse)
        {
            view_inverse_mat = glm::inverse(get_view());

            flags &= ~dirty_inverse;
        }

        return view_inverse_mat;
    }

    void camera::update_frame_id()
    {
        try {
            get<way_path>()->point(frame_id);
        } catch (path_line::no_point) {
            frame_id = get<way_path>()->first_index();
        }


        auto cam_sqdist = [this](int idx) -> float {
            auto frpos = get<way_path>()->point(idx).get_position();

            return math::sqdist(get_position(), frpos);
        };


        while (get<way_path>()->first_index() < frame_id
                and cam_sqdist(frame_id - 1)
                < cam_sqdist(frame_id))
        {
            frame_id--;
        }

        while (get<way_path>()->last_index() > frame_id
                and cam_sqdist(frame_id + 1)
                < cam_sqdist(frame_id))
        {
            frame_id++;
        }
    }
}
