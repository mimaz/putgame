/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/gui>
#include <putgame/world>

#include "application.hxx"

#include "main_menu.hxx"

namespace 
{
    enum
    {
        flag_running = 0x01,
    };
}

namespace game
{
    application::application()
        : flags(0)
    {}
    
    void application::run()
    {
        glClearColor(0, 0, 0, 1);
        glFrontFace(GL_CW);

        window = make_window();
        flags |= flag_running;


        for (auto i = 0; i < 100; i++)
            get_part<world::way_path>()->generate();


        auto menu = std::make_unique<main_menu>(this);
        auto box = std::make_unique<world::light_box>
            (this, world::light_box::green);


        auto next_time = window->get_time_millis();

        while (flags & flag_running)
        {
            auto time = window->get_time_millis();

            if (time < next_time)
                continue;

            next_time += 1000 / 50;

            get_part<world::camera>()->rotate(PI / 50, glm::vec3(0, 1, 0));

            get_part<world::draw_manager>()->draw_all();

            get_part<gui::surface>()->preprocess();
            get_part<gui::surface>()->draw();

            window->swap_buffers();
        }
    }

    void application::rotate(float angle, glm::vec3 axis)
    {

    }

    void application::move(glm::vec3 vec)
    {

    }

    void application::resize(int width, int height)
    {
        auto ratio = static_cast<float>(width) / height;

        get_part<world::camera>()->set_view_ratio(ratio);
        get_part<gui::surface>()->resize(width, height);
    }

    void application::cursor(int x, int y)
    {
        xpos = x;
        ypos = y;

        gui::touch_event event(gui::touch_event::move, x, y);

        get_part<gui::surface>()->touch(event);
    }

    void application::press()
    {
        gui::touch_event event(gui::touch_event::press, xpos, ypos);

        get_part<gui::surface>()->touch(event);
    }

    void application::release()
    {
        gui::touch_event event(gui::touch_event::release, xpos, ypos);

        get_part<gui::surface>()->touch(event);
    }

    void application::exit()
    {
        flags &= ~flag_running;
    }
}
