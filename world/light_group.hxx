/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_light_group_hxx
#define __world_light_group_hxx

#include "context_part.hxx"

namespace world
{
    class light_group : public context_part
    {
    public:
        light_group(context *ctx);
    };
}

#endif
