/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_draw_manager_hxx
#define __world_draw_manager_hxx

#include "context_part.hxx"

namespace world
{
    class light_box;
    class light_box_view;

    class wall_obstacle;
    class wall_obstacle_view;

    class glass_pane;
    class glass_pane_view;

    class tunnel_view;

    class draw_manager : public context_part
    {
    public:
        draw_manager(context *ctx);

        void add(light_box *box);
        void remove(light_box *box);

        void add(wall_obstacle *box);
        void remove(wall_obstacle *box);

        void add(glass_pane *box);
        void remove(glass_pane *box);

        void draw_all();

    private:
        std::set<light_box *> light_boxes;
        std::set<wall_obstacle *> wall_obstacles;
        std::set<glass_pane *> glass_panes;

        std::shared_ptr<light_box_view> light_box_drawer;
        std::shared_ptr<wall_obstacle_view> wall_obstacle_drawer;
        std::shared_ptr<glass_pane_view> glass_pane_drawer;
        std::shared_ptr<tunnel_view> tunnel_drawer;
    };
}

#endif
