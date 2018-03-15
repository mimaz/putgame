/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std.hxx>

#include "camera.hxx"

namespace world
{
    camera::camera()
        : proj_mat(1)
        , view_mat(1)
    {

    }

    camera::~camera()
    {

    }

    glm::mat4 camera::get_proj() const
    {
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
}
