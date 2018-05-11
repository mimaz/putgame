/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/gui>
#include <putgame/math>
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


        get_part<world::camera>()->rotate(math::pi, glm::vec3(0, 1, 0));
        get_part<world::camera>()->move(glm::vec3(0, 0, -4));


        //auto menu = std::make_unique<main_menu>(this);
        auto white_box = std::make_unique<world::light_box>
            (this, 40, world::light_box::white);

        white_box->scale(0.25f);


        auto wall = std::make_unique<world::wall_obstacle>
            (this, 5, 12, 8);


        auto pieces = std::make_unique<world::glass_pieces>
            (this, 100, glm::vec3(0, 0, 1), glm::vec2(4, 4), glm::mat4(1));


        auto next_time = time_millis();

        while (flags & flag_running)
        {
            auto time = time_millis();

            if (time < next_time)
                continue;

            next_time += 1000 / 50;

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            get_part<world::object_manager>()->process_all();
            get_part<world::object_manager>()->draw_all();

            get_part<gui::surface>()->preprocess();
            get_part<gui::surface>()->draw();

            window->swap_buffers();
        }
    }

    void application::rotate(float angle, glm::vec3 axis)
    {
        get_part<world::camera>()->rotate(angle, axis);
    }

    void application::move(glm::vec3 vec)
    {
        get_part<world::camera>()->move(vec);
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
