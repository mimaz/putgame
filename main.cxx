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
