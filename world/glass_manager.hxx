/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_glass_manager_hxx
#define __world_glass_manager_hxx

#include "context_part.hxx"

namespace world
{
    class glass_pane;
    class glass_view;

    class glass_manager : public context_part
    {
    public:
        glass_manager(context *ctx);

        void add(glass_pane *pane);
        void remove(glass_pane *pane);

        void draw_all();

    private:
        std::set<glass_pane *> panes;

        std::shared_ptr<glass_view> view;
    };
}

#endif
