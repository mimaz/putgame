/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/world>
#include <putgame/math>
#include <putgame/gui>

#include "instance.hxx"

#include "activity.hxx"
#include "main_menu.hxx"

namespace game
{
    instance::instance()
        : mouse_x(-1)
        , mouse_y(-1)
        , mouse_pressed(false)
        , shifting(false)
    {}

    instance::~instance()
    {}

    void instance::start()
    {
        glClearColor(0, 0.0, 0, 1);
        glFrontFace(GL_CW);

        play = std::make_shared<activity>(this);
        menu = std::make_shared<main_menu>(this);
    }

    void instance::stop()
    {
        play = nullptr;
        menu = nullptr;
    }

    void instance::draw()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        get<world::object_manager>()->draw_all();
        get<gui::surface>()->draw();
    }

    void instance::process()
    {
        if (menu != nullptr)
            menu->process();

        if (play != nullptr)
            play->process();

        get<world::object_manager>()->process_all();
        get<gui::surface>()->process();
    }

    void instance::resize(int wid, int hei)
    {
        auto ratio = static_cast<float>(wid) / hei;

        width = wid;
        height = hei;

        get<gui::surface>()->resize(wid, hei);
        get<world::camera>()->set_view_ratio(ratio);

        glViewport(0, 0, wid, hei);
    }

    void instance::cursor(int x, int y)
    {
        if (x == mouse_x and y == mouse_y)
            return;

        x -= get_width() / 2;
        y -= get_height() / 2;

        if (mouse_pressed)
        {
            if (shifting)
            {
                auto diffx = static_cast<float>(x - mouse_x) 
                           / get_width();
                auto diffy = static_cast<float>(y - mouse_y) 
                           / get_height();

                if (play != nullptr)
                    play->steer(diffx, diffy);
            }
            else
            {
                shifting = true;
            }

            gui::touch_event event(gui::touch_event::move, x, y);

            get<gui::surface>()->touch(event);
        }
        else
        {
            shifting = false;
        }

        mouse_x = x;
        mouse_y = y;
    }

    void instance::press()
    {
        mouse_pressed = true;

        gui::touch_event event(gui::touch_event::press, 
                               mouse_x, mouse_y);

        get<gui::surface>()->touch(event);
    }

    void instance::release()
    {
        mouse_pressed = false;

        gui::touch_event event(gui::touch_event::release, 
                               mouse_x, mouse_y);

        get<gui::surface>()->touch(event);
    }

    int instance::get_width() 
    {
        return width;
    }

    int instance::get_height()
    {
        return height;
    }
}
