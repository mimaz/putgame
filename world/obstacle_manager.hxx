/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_obstacle_manager_hxx
#define __world_obstacle_manager_hxx

#include "context_part.hxx"

namespace world
{
    class abstract_obstacle;
    class wall_obstacle;
    class wall_obstacle_view;

    class obstacle_manager : public context_part
    {
    public:
        obstacle_manager(context *ctx);

        void add(wall_obstacle *obst);
        void remove(abstract_obstacle *obst);

        void draw_all();

    private:
        std::set<wall_obstacle *> walls;

        std::shared_ptr<wall_obstacle_view> wall_view;
    };
}

#endif
