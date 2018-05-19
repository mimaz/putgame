/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/world>
#include <putgame/math>
#include <putgame/gui>

#include "context.hxx"
#include "play_activity.hxx"

namespace game
{
    context::context()
    {
    }

    context::~context()
    {
        get<world::object_manager>()->join_process();
    }

    void context::start()
    {
        glClearColor(0, 0, 0, 1);
        glFrontFace(GL_CW);

        play = std::make_shared<play_activity>(this);
    }

    void context::stop()
    {
        play = nullptr;
    }

    void context::draw()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        get<world::object_manager>()->process_all();
        get<gui::surface>()->process();

        get<world::object_manager>()->draw_all();
        get<gui::surface>()->draw();

        if (play != nullptr)
            play->on_draw();

        swap_buffers();
    }

    void context::resize(int wid, int hei)
    {
        auto ratio = static_cast<float>(wid) / hei;

        width = wid;
        height = hei;

        get<gui::surface>()->resize(wid, hei);
        get<world::camera>()->set_view_ratio(ratio);

        glViewport(0, 0, wid, hei);
    }

    void context::cursor(int x, int y)
    {
        if (x == mouse_x and y == mouse_y)
            return;

        mouse_x = x;
        mouse_y = y;

        if (mouse_pressed)
        {
            gui::touch_event event(gui::touch_event::move, x, y);

            get<gui::surface>()->touch(event);
        }
    }

    void context::press()
    {
        gui::touch_event event(gui::touch_event::press, 
                               mouse_x, mouse_y);

        get<gui::surface>()->touch(event);
    }

    void context::release()
    {
        gui::touch_event event(gui::touch_event::release, 
                               mouse_x, mouse_y);

        get<gui::surface>()->touch(event);
    }
}
