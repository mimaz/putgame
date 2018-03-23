/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_way_path_hxx
#define __world_way_path_hxx

#include "context.hxx"
#include "path_line.hxx"

namespace world
{
    class way_path : public context::part, public path_line
    {
    public:
        way_path(context *ctx);

        void generate();
    };
}

#endif
