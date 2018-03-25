/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_way_path_hxx
#define __world_way_path_hxx

#include <putgame/common>

#include "path_line.hxx"

namespace world
{
    class way_path : public common::context::part, public path_line
    {
    public:
        way_path(common::context *ctx);

        void generate();
    };
}

#endif
