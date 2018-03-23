/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "wall_obstacle_manager.hxx"

#include "wall_obstacle_view.hxx"

namespace world
{
    wall_obstacle_manager::wall_obstacle_manager(context *ctx)
        : object_manager(ctx)
    {}

    wall_obstacle_view *wall_obstacle_manager::new_view()
    {
        return new wall_obstacle_view(get_context());
    }
}
