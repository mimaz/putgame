/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_light_group_hxx
#define __world_light_group_hxx

#include "context.hxx"

namespace world
{
    class light_source;

    class light_group : public context::part
    {
    public:
        light_group(context *ctx);

        void register_source(light_source *src);
        void unregister_source(light_source *src);

        const std::set<light_source *> get_all() const { return sources; }

    private:
        std::set<light_source *> sources;
    };
}

#endif
