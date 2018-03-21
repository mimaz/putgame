/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_wall_obstacle_hxx
#define __world_wall_obstacle_hxx

#include "abstract_obstacle.hxx"

namespace world
{
    class wall_obstacle : public abstract_obstacle
    {
    public:
        wall_obstacle(context *ctx, glm::vec2 siz);

        glm::vec2 get_size() const { return size; }

    private:
        glm::vec2 size;
    };
}

#endif
