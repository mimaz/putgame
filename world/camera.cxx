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
};

constexpr auto near_plane = 0.01f;

namespace world
{
    camera::camera(common::context *ctx)
        : object(ctx)
        , light_source(ctx)
        , flags(dirty_proj | dirty_view_proj)
        , proj_mat(1)
        , view_mat(1)
        , view_angle(math::pi / 3)
        , view_ratio(1)
        , view_range(32)
    {}

    void camera::move(float x, float y, float z)
    {
        move(glm::vec3(x, y, z));
    }

    void camera::move(const glm::vec3 &vec)
    {
        flags |= dirty_view_proj;
        view_mat = glm::translate(glm::mat4(1), -vec) * view_mat;

        get_part<way_path>()->camera_moved();
    }

    void camera::rotate(float angle, const glm::vec3 &axis)
    {
        flags |= dirty_view_proj;
        view_mat = glm::rotate(glm::mat4(1), -angle, axis) * view_mat;
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

    const glm::mat4 &camera::get_proj() const
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

    const glm::mat4 &camera::get_view() const
    {
        return view_mat;
    }

    const glm::mat4 &camera::get_view_proj() const
    {
        if (flags & dirty_view_proj)
        {
            flags &= ~dirty_view_proj;

            view_proj_mat = get_proj() * get_view();
        }

        return view_proj_mat;
    }

    glm::mat4 camera::make_mvp(const glm::mat4 &model) const
    {
        return get_view_proj() * model;
    }

    glm::vec3 camera::get_position() const
    {
        return math::coord3d(inversed_view());
    }

    glm::vec3 camera::get_direction() const
    {
        return -math::direction3d(inversed_view());
    }

    glm::vec3 camera::get_top() const
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
        return 15;
    }

    glm::mat4 camera::inversed_view() const
    {
        return glm::inverse(get_view());
    }
}
