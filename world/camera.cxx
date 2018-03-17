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
        , flags(dirty_proj | dirty_mvp)
        , proj_mat(1)
        , view_mat(1)
        , view_angle(PI / 4)
        , view_ratio(1)
        , view_range(16)
    {
        view_mat = glm::translate(glm::mat4(1), glm::vec3(0, 0.0f, 4.0f));

        //rotate(PI / 10, { 0, 1, 0 });
        //move({ 1.5f, 0.0f, 0.0f });
    }

    camera::~camera()
    {}

    void camera::move(const glm::vec3 &vec)
    {
        view_mat = glm::translate(view_mat, vec);
    }

    void camera::rotate(float angle, const glm::vec3 &axis)
    {
        view_mat = glm::rotate(view_mat, angle, axis);
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

    glm::mat4 camera::get_mvp(const glm::mat4 &model) const
    {
        return get_proj() * get_view() * model;
    }

    glm::vec3 camera::get_position() const
    {
        // TODO it may be needed to invert w-axis
        return glm::vec3(get_view() * glm::vec4(0, 0, 0, 1));
    }

    glm::vec3 camera::get_direction() const
    {
        // TODO it may be needed to invert z-axis
        return glm::vec3(get_view() * glm::vec4(0, 0, 1, 0));
    }
}
