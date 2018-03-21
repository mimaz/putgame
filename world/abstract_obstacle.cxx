/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "abstract_obstacle.hxx"

#include "context.hxx"
#include "obstacle_manager.hxx"
#include "wall_obstacle.hxx"

namespace world
{
    abstract_obstacle::abstract_obstacle(context *ctx)
        : visible_object(ctx)
    {}

    abstract_obstacle::~abstract_obstacle()
    {
        get_context()->get_part<obstacle_manager>()->remove(this);
    }

      template<typename _Type>
    void abstract_obstacle::register_self(_Type *self)
    {
        static_cast<abstract_obstacle *>(self)
            ->get_context()
            ->get_part<obstacle_manager>()
            ->add(self);
    }

    template void 
    abstract_obstacle::register_self
    <wall_obstacle>(wall_obstacle *);
}
