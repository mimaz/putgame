/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_wall_obstacle_hxx
#define __world_wall_obstacle_hxx

#include "visible_object.hxx"

namespace world
{
    class wall_obstacle : public visible_object
    {
    public:
        wall_obstacle(common::context *ctx, 
                      int frameid, 
                      int w, int h, int d = 1);
        ~wall_obstacle();

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
