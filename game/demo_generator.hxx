/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_demo_generator_hxx
#define __game_demo_generator_hxx

#include "object_generator.hxx"

namespace game
{
    class demo_generator : public object_generator
    {
    public:
        demo_generator(play_activity *act);

        void generate() override;
    };
}

#endif
