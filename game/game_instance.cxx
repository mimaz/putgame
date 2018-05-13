/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/world>
#include <putgame/math>
#include <putgame/gui>

#include "game_instance.hxx"
#include "main_stage.hxx"

namespace game
{
    game_instance::game_instance()
    {
    }

    game_instance::~game_instance()
    {
        get_part<world::object_manager>()->join_process();
    }

    void game_instance::start()
    {
        glClearColor(0, 0, 0, 1);
        glFrontFace(GL_CW);

        main_st = std::make_shared<main_stage>(this);

        get_part<world::camera>()->rotate(math::pi, glm::vec3(0, 1, 0));
    }

    void game_instance::stop()
    {
        main_st = nullptr;
    }

    void game_instance::draw()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        get_part<world::object_manager>()->draw_all();
        get_part<gui::surface>()->draw();

        get_part<world::object_manager>()->process_all();
        get_part<gui::surface>()->process();

        swap_buffers();
    }

    void game_instance::resize(int wid, int hei)
    {
        width = wid;
        height = hei;

        glViewport(0, 0, wid, hei);

        get_part<gui::surface>()->resize(wid, hei);
    }

    void game_instance::cursor(int x, int y)
    {
        if (x == mouse_x and y == mouse_y)
            return;

        mouse_x = x;
        mouse_y = y;

        if (mouse_pressed)
        {
            gui::touch_event event(gui::touch_event::move, x, y);

            get_part<gui::surface>()->touch(event);
        }
    }

    void game_instance::press()
    {
        gui::touch_event event(gui::touch_event::press, 
                               mouse_x, mouse_y);

        get_part<gui::surface>()->touch(event);
    }

    void game_instance::release()
    {
        gui::touch_event event(gui::touch_event::release, 
                               mouse_x, mouse_y);

        get_part<gui::surface>()->touch(event);
    }
}
