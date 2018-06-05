/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */


#include "object_manager.hxx"

#include "light_box.hxx"
#include "light_box_view.hxx"
#include "wall_obstacle_view.hxx"
#include "glass_pane_view.hxx"
#include "glass_pieces_view.hxx"
#include "glass_pieces.hxx"
#include "tunnel_view.hxx"
#include "way_path.hxx"

namespace world
{
    object_manager::object_manager(common::context *ctx)
        : object(ctx)
        , light_box_drawer(std::make_shared<light_box_view>(ctx))
        , wall_obstacle_drawer(std::make_shared<wall_obstacle_view>(ctx))
        , glass_pane_drawer(std::make_shared<glass_pane_view>(ctx))
        , glass_pieces_drawer(std::make_shared<glass_pieces_view>(ctx))
    {}

    object_manager::~object_manager()
    {
        if (process_thread != nullptr)
            process_thread->join();
    }

    void object_manager::add(light_box *box)
    { light_boxes.insert(box); }

    void object_manager::remove(light_box *box)
    { light_boxes.erase(box); }

    void object_manager::add(wall_obstacle *wall)
    { wall_obstacles.insert(wall); }

    void object_manager::remove(wall_obstacle *wall)
    { wall_obstacles.erase(wall); }

    void object_manager::add(glass_pane *pane)
    { glass_panes.insert(pane); }

    void object_manager::remove(glass_pane *pane)
    { glass_panes.erase(pane); }

    void object_manager::add(glass_pieces *pieces)
    { 
        std::lock_guard<std::mutex> guard(process_lock);

        glass_pieces_set.insert(pieces); 
    }

    void object_manager::remove(glass_pieces *pieces)
    { 
        std::lock_guard<std::mutex> guard(process_lock);

        glass_pieces_set.erase(pieces); 
    }

    void object_manager::draw_all()
    {
        get<tunnel_view>()->draw();
        


        light_box_drawer->begin_drawing();

        for (auto box : light_boxes)
            light_box_drawer->draw_element(box);

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

    void object_manager::process_all()
    {
        join_process();

        for (auto box : light_boxes)
            box->process();

        for (auto pieces : glass_pieces_set)
            pieces->update();

        get<way_path>()->update();
        get<tunnel_view>()->get_path()->update();
    }

    void object_manager::join_process()
    {
        if (process_thread != nullptr)
        {
            process_thread->join();
            process_thread = nullptr;
        }
    }
}
