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
        : width(1)
        , height(1)
        , mouse_x(-1)
        , mouse_y(-1)
        , mouse_pressed(false)
        , shifting(false)
    {
        set_property("fps", property_value(30));
    }

    instance::~instance()
    {}

    void instance::start()
    {
        glClearColor(0, 0, 0, 1);
        glFrontFace(GL_CW);
    }

    void instance::stop()
    {
        destroy<activity>();
        destroy<main_menu>();
    }

    void instance::draw()
    {
        get<activity>()->process();
        get<main_menu>()->process();

        get<world::object_manager>()->process_all();
        get<gui::surface>()->process();


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        get<world::object_manager>()->draw_all();
        get<gui::surface>()->draw();
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

        common::logd("cursor: ", x, " : ", y);

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

                get<activity>()->steer(diffx, diffy);
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

    void instance::key(keycode kc)
    {
        constexpr float scalar = 0.04f;

        auto off_x = [this]() { 
            return static_cast<int>(get_width() * scalar); 
        };

        auto off_y = [this]() {
            return static_cast<int>(get_height() * scalar); 
        };

        press();

        int x = mouse_x + get_width() / 2;
        int y = mouse_y + get_height() / 2;

        switch (kc)
        {
        case keycode::left:
            cursor(x + off_x(), y);
            break;

        case keycode::right:
            cursor(x - off_x(), y);
            break;

        case keycode::up:
            cursor(x, y - off_y());
            break;

        case keycode::down:
            cursor(x, y + off_y());
            break;

        case keycode::start:
            get<activity>()->switch_state(activity::play);
            break;

        default:
            common::loge("invalid dir value!");
        }

        release();
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
