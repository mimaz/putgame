/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "light_group.hxx"

namespace world
{
    light_group::light_group(common::context *ctx)
        : common::context::part(ctx)
    {}

    void light_group::register_source(light_source *src)
    {
        sources.insert(src);
    }

    void light_group::unregister_source(light_source *src)
    {
        sources.erase(src);
    }
}
