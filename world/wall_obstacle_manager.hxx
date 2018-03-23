/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_wall_obstacle_manager_hxx
#define __world_wall_obstacle_manager_hxx

#include "object_manager.hxx"

namespace world
{
    class wall_obstacle;
    class wall_obstacle_view;
    
    class wall_obstacle_manager 
    : public object_manager<wall_obstacle, wall_obstacle_view>
    {
    public:
        wall_obstacle_manager(context *ctx);

    protected:
        wall_obstacle_view *new_view() override;

    private:
    };
}

#endif
