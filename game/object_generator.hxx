/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_object_generator_hxx
#define __game_object_generator_hxx

#include <putgame/common>

namespace game
{
    class object_generator : public common::context::object
    {
    public:
        PUTGAME_OBJECT

        object_generator(common::context *ctx);

        void generate();
    };
}

#endif
