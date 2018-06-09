/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */


#include "light_source.hxx"

#include "light_group.hxx"

namespace world
{
    light_source::light_source(common::context *ctx)
        : light_source(ctx->get<light_group>()) {}

    light_source::light_source(light_group *grp)
        : grp(grp)
    {
        grp->register_source(this);
    }

    light_source::~light_source()
    {
        if (grp != nullptr)
            grp->unregister_source(this);
    }

    void light_source::detach()
    {
        grp = nullptr;
    }
}
