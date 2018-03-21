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
        wall_obstacle(context *ctx, int w, int h);
        wall_obstacle(context *ctx, int w, int h, int d);

        int get_width() const { return width; }
        int get_height() const { return height; }
        int get_depth() const { return depth; }

    private:
        int width;
        int height;
        int depth;
    };
}

#endif
