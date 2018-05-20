/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "object_generator.hxx"

#include "play_activity.hxx"

namespace game
{
    object_generator::object_generator(play_activity *activity)
        : object(activity)
        , activity(activity)
    {}

    void object_generator::on_draw()
    {
        std::cout << "generate!" << std::endl;
    }
}
