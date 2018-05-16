/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "visible_object.hxx"
#include "way_path.hxx"

namespace world
{
    visible_object::visible_object(common::context *ctx,
                                   int frameid)
        : object(ctx) 
        , frame_id(frameid)
    {
        auto point = get_part<way_path>()->point(frameid);

        apply(point.get_matrix());
    }

    void visible_object::set_matrix(const glm::mat4 &mat)
    {
        model = mat;
    }

    void visible_object::apply(const glm::mat4 &mat)
    {
        model *= mat;
    }

    void visible_object::translate(float x, float y, float z)
    {
        translate(glm::vec3(x, y, z));
    }

    void visible_object::scale(float scalar)
    {
        scale(scalar, scalar, scalar);
    }

    void visible_object::scale(float x, float y, float z)
    {
        scale(glm::vec3(x, y, z));
    }

    void visible_object::translate(const glm::vec3 &vec)
    {
        model = glm::translate(model, vec);
    }

    void visible_object::rotate(float angle, const glm::vec3 &axis)
    {
        model = glm::rotate(model, angle, axis);
    }

    void visible_object::scale(const glm::vec3 &vec)
    {
        model = glm::scale(model, vec);
    }

    const glm::mat4 &visible_object::get_model() const
    {
        return model;
    }

    glm::vec3 visible_object::get_position() const
    {
        return glm::vec3(get_model() * glm::vec4(0, 0, 0, 1));
    }
}
