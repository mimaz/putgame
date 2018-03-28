/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>
#include <putgame/text>
#include <putgame/glutils>
#include <putgame/gui>
#include <putgame/world>

#include "glfw_window.hxx"
#include "main_menu.hxx"

static void error_callback(int code, const char *desc)
{
    std::cerr << "GLFW error: " << code << ": " << desc << std::endl;
    exit(1);
}

int main(void)
{
    assert(glfwInit());
    glfwSetErrorCallback(error_callback);

    auto win = new glfw_window(1920, 1080, "putgame");

    for (auto i = 0; i < 100; i++)
        win->get_part<world::way_path>()->generate();

    try {
        auto menu = std::make_unique<main_menu>(win);
        auto pane = std::make_unique<world::glass_pane>
            (win, glm::vec3(1, 0, 0), glm::vec2(3.0f, 0.75f));

        pane->translate(glm::vec3(-0.1f, 0, -3.5f));
        pane->rotate(PI / 8, glm::vec3(0, 1, 0));


        auto redbox = std::make_unique<world::light_box>
            (win, world::light_box::red);

        redbox->translate(glm::vec3(-0.6f, -0.25f, -3.0f));
        redbox->scale(0.25f);



        auto greenbox = std::make_unique<world::light_box>
            (win, world::light_box::green);

        greenbox->translate(glm::vec3(0.6f, 0.25f, -3.4f));
        greenbox->scale(0.25f);




        auto bluebox = std::make_unique<world::light_box>
            (win, world::light_box::blue);

        bluebox->translate(glm::vec3(-0.4f, 0.0f, -5.0f));
        bluebox->scale(0.25f);



        auto next_time = glfwGetTime();

        while (not win->should_close())
        {
            auto time = glfwGetTime();

            if (time >= next_time)
            {
                next_time += 1.0 / 50;

                win->draw();
            }
        }
    } catch (glutils::shader_error e) {
        std::cerr << "shader_error: " << e.log << std::endl;
    }


    delete win;

    glfwTerminate();

    return 0;
}
