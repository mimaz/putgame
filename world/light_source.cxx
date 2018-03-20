/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "light_source.hxx"

#include "light_group.hxx"
#include "context.hxx"

namespace world
{
    light_source::light_source(context *ctx)
        : light_source(ctx->get_part<light_group>()) {}

    light_source::light_source(light_group *grp)
        : grp(grp)
    {
        grp->register_source(this);
    }

    light_source::~light_source()
    {
        grp->unregister_source(this);
    }
}