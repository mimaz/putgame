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
    class glass_piece;
    class glass_view;

    class glass_manager : public context_part
    {
    public:
        glass_manager(context *ctx);

        void add(glass_pane *pane);
        void add(glass_piece *pane);
        
        void remove(glass_pane *pane);
        void remove(glass_piece *pane);

        void draw_all();
        void draw_all_specular();

    private:
        void draw(bool specular);

        std::set<glass_pane *> panes;
        std::set<glass_piece *> pieces;

        std::shared_ptr<glass_view> view;
    };
}

#endif
