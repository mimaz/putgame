/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>

#include "way_path.hxx"

namespace world
{
    way_path::way_path(context *ctx)
        : context::part(ctx)
        , path_line(1)
    {}

    void way_path::generate()
    {
        append(PI / 80, { 0, 1, 0 });
        // TODO generate default path
    }
}
