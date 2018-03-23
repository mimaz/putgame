/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "glass_pane_manager.hxx"
#include "glass_pane_view.hxx"

namespace world
{
    glass_pane_manager::glass_pane_manager(context *ctx)
        : object_manager(ctx)
    {}

    glass_pane_view *glass_pane_manager::new_view()
    {
        return new glass_pane_view(get_context());
    }
}
