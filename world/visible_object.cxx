/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "visible_object.hxx"

#include "context.hxx"

namespace world
{
    visible_object::visible_object(context *ctx)
        : ctx(ctx) 
    {}

    visible_object::~visible_object() 
    {}

    void visible_object::detach()
    {
        ctx = nullptr;
    }

    void visible_object::set_matrix(const glm::mat4 &mat)
    {
        model = mat;
    }

    void visible_object::move(const glm::vec3 &vec)
    {
        model = glm::translate(glm::mat4(1), vec) * model;
    }

    void visible_object::rotate(float angle, const glm::vec3 &axis)
    {
        model = glm::rotate(model, angle, axis);
    }

    void visible_object::scale(float scalar)
    {
        scale(glm::vec3(scalar, scalar, scalar));
    }

    void visible_object::scale(const glm::vec3 &vec)
    {
        model = glm::scale(model, vec);
    }

    glm::vec3 visible_object::get_position() const
    {
        return glm::vec3(get_model() * glm::vec4(0, 0, 0, 1));
    }
}
