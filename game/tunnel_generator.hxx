/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_tunnel_generator_hxx
#define __game_tunnel_generator_hxx

#include <putgame/world>

namespace game
{
    class tunnel_generator : public common::context::object
    {
    public:
        PUTGAME_OBJECT

        tunnel_generator(common::context *ctx);

        world::way_path::segment_ref generate();
    };
}

#endif
