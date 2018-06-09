/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_tunnel_generator_hxx
#define __game_tunnel_generator_hxx

#include <putgame/world>

#include "object.hxx"

namespace game
{
    class tunnel_generator : public object
    {
    public:
        tunnel_generator(activity *act);

        world::way_path::segment_ref generate();
    };
}

#endif
