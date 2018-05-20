/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_object_generator_hxx
#define __game_object_generator_hxx

#include <putgame/common>

namespace game
{
    class play_activity;

    class object_generator : public common::context::object
    {
    public:
        object_generator(play_activity *activity);

        void on_draw();

    private:
        play_activity *activity;
    };
}

#endif