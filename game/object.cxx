/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include "object.hxx"

#include "instance.hxx"

namespace game
{
    object::object(common::context::object *obj)
        : common::context::object(obj)
    {}

    object::object(common::context *ctx)
        : common::context::object(ctx)
    {}

    activity *object::get_activity() const
    {
        return static_cast<instance *>(get_context())->get_activity();
    }
}
