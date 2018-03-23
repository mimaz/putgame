/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_glass_pane_manager_hxx
#define __world_glass_pane_manager_hxx

#include "object_manager.hxx"

namespace world
{
    class glass_pane;
    class glass_pane_view;

    class glass_pane_manager 
    : public object_manager<glass_pane, glass_pane_view>
    {
    public:
        glass_pane_manager(context *ctx);

    protected:
        glass_pane_view *new_view() final;
    };
}

#endif
