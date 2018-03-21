/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "camera.hxx"

enum
{
    dirty_proj = 0x01,
    dirty_mvp = 0x02,
};

constexpr auto near_plane = 0.01f;

namespace world
{
    camera::camera(context *ctx)
        : context_part(ctx)
        , light_source(ctx)
        , flags(dirty_proj | dirty_mvp)
        , proj_mat(1)
        , view_mat(1)
        , view_angle(PI / 4)
        , view_ratio(1)
        , view_range(64)
    {}

    camera::~camera()
    {}

    void camera::move(const glm::vec3 &vec)
    {
        view_mat = glm::translate(glm::mat4(1), -vec) * view_mat;
    }

    void camera::rotate(float angle, const glm::vec3 &axis)
    {
        view_mat = glm::rotate(glm::mat4(1), -angle, axis) * view_mat;
    }

    void camera::set_view_angle(float angle)
    {
        flags |= dirty_proj | dirty_mvp;
        view_angle = angle;
    }

    void camera::set_view_ratio(float ratio)
    {
        flags |= dirty_proj | dirty_mvp;
        view_ratio = ratio;
    }

    void camera::set_view_range(float range)
    {
        flags |= dirty_proj | dirty_mvp;
        view_range = range;
    }

    glm::mat4 camera::get_proj() const
    {
        if (flags & dirty_proj)
        {
            flags &= ~dirty_proj;

            proj_mat = glm::perspective(get_view_angle(), 
                                        get_view_ratio(),
                                        near_plane,
                                        get_view_range());

            proj_mat[2] *= -1;
        }

        return proj_mat;
    }

    glm::mat4 camera::get_view() const
    {
        return view_mat;
    }

    glm::mat4 camera::make_mvp(const glm::mat4 &model) const
    {
        return get_proj() * get_view() * model;
    }

    glm::vec3 camera::get_position() const
    {
        auto inv = glm::inverse(get_view());

        return glm::vec3(inv * glm::vec4(0, 0, 0, 1));
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
        return 100;
    }
}
