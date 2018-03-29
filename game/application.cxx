/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/gui>

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


        auto menu = std::make_unique<main_menu>(this);

        auto next_time = window->get_time_millis();

        while (flags & flag_running)
        {
            auto time = window->get_time_millis();

            if (time < next_time)
                continue;

            next_time += 1000 / 50;


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

    void application::exit()
    {
        flags &= ~flag_running;
    }
}
