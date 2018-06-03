/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */


#include "object_generator.hxx"

#include "play_activity.hxx"

namespace game
{
    object_generator::object_generator(play_activity *activity)
        : object(activity)
        , activity(activity)
    {}

    object_generator::~object_generator() {}

    void object_generator::generate()
    {}
}
