/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include "light_group.hxx"

#include "light_source.hxx"

namespace world
{
    light_group::light_group(common::context *ctx)
        : object(ctx)
    {}

    light_group::~light_group()
    {
        for (auto src : sources)
            src->detach();
    }

    void light_group::register_source(light_source *src)
    {
        sources.insert(src);
    }

    void light_group::unregister_source(light_source *src)
    {
        sources.erase(src);
    }

    const std::set<light_source *> light_group::get_all() const
    {
        return sources;
    }
}
