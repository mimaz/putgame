/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "draw_manager.hxx"

#include "light_box.hxx"
#include "light_box_view.hxx"
#include "wall_obstacle_view.hxx"
#include "glass_pane_view.hxx"
#include "glass_pieces_view.hxx"
#include "tunnel_view.hxx"

namespace world
{
    draw_manager::draw_manager(common::context *ctx)
        : common::context::part(ctx)
        , light_box_drawer(std::make_shared<light_box_view>(ctx))
        , wall_obstacle_drawer(std::make_shared<wall_obstacle_view>(ctx))
        , glass_pane_drawer(std::make_shared<glass_pane_view>(ctx))
        , glass_pieces_drawer(std::make_shared<glass_pieces_view>(ctx))
        , tunnel_drawer(std::make_shared<tunnel_view>(ctx, 16))
    {}

    void draw_manager::add(light_box *box)
    { light_boxes.insert(box); }

    void draw_manager::remove(light_box *box)
    { light_boxes.erase(box); }

    void draw_manager::add(wall_obstacle *wall)
    { wall_obstacles.insert(wall); }

    void draw_manager::remove(wall_obstacle *wall)
    { wall_obstacles.erase(wall); }

    void draw_manager::add(glass_pane *pane)
    { glass_panes.insert(pane); }

    void draw_manager::remove(glass_pane *pane)
    { glass_panes.erase(pane); }

    void draw_manager::add(glass_pieces *pieces)
    { glass_pieces_set.insert(pieces); }

    void draw_manager::remove(glass_pieces *pieces)
    { glass_pieces_set.erase(pieces); }

    void draw_manager::draw_all()
    {
        tunnel_drawer->draw();
        return;
        


        light_box_drawer->begin_drawing();

        for (auto box : light_boxes)
        {
            box->rotate();

            light_box_drawer->draw_element(box);
        }

        light_box_drawer->end_drawing();



        wall_obstacle_drawer->begin_drawing();

        for (auto wall : wall_obstacles)
            wall_obstacle_drawer->draw_element(wall);
        
        wall_obstacle_drawer->end_drawing();



        glass_pane_drawer->begin_drawing();

        for (auto pane : glass_panes)
            glass_pane_drawer->draw_element(pane);

        glass_pane_drawer->end_drawing();



        glass_pieces_drawer->begin();

        for (auto pieces : glass_pieces_set)
            glass_pieces_drawer->draw(pieces);

        glass_pieces_drawer->end();
    }
}
