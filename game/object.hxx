/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_object_hxx
#define __game_object_hxx

#include <putgame/common>

namespace game
{
    class activity;

    class object : public common::context::object
    {
    public:
        object(common::context::object *obj);
        object(common::context *ctx);
        object(activity *act);

        activity *get_activity() const;
    };
}

#endif
