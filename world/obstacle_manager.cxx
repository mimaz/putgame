/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "obstacle_manager.hxx"

#include "wall_obstacle.hxx"
#include "wall_obstacle_view.hxx"

namespace world
{
    obstacle_manager::obstacle_manager(context *ctx)
        : context_part(ctx)
        , wall_view(std::make_shared<wall_obstacle_view>(ctx))
    {}

    void obstacle_manager::add(wall_obstacle *wall)
    {
        walls.insert(wall);
    }

    void obstacle_manager::remove(abstract_obstacle *obst)
    {
        walls.erase(static_cast<wall_obstacle *>(obst));
    }

    void obstacle_manager::draw_all()
    {
        wall_view->begin();

        for (auto wall : walls)
            wall_view->draw(wall);

        wall_view->end();
    }
}
