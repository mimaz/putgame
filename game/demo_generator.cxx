/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "demo_generator.hxx"

namespace game
{
    demo_generator::demo_generator(play_activity *act)
        : object_generator(act)
    {}

    void demo_generator::on_draw()
    {
        object_generator::on_draw();
    }
}
