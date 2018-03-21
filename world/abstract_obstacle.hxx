/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_abstract_obstacle_hxx
#define __world_abstract_obstacle_hxx

#include "visible_object.hxx"

namespace world
{
    class abstract_obstacle : public visible_object
    {
    public:
        abstract_obstacle(context *ctx);
        ~abstract_obstacle();

          template<typename _Type>
        static void register_self(_Type *self);

          template<typename _Type>
        static void unregister_self(_Type *self);
    };
}

#endif
