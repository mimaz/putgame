/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>
#include <putgame/text>
#include <putgame/glutils>
#include <putgame/gui>

#include "glfw_window.hxx"

static void error_callback(int code, const char *desc)
{
    std::cerr << "GLFW error: " << code << ": " << desc << std::endl;
    exit(1);
}

int main(void)
{
    constexpr auto default_width = 1920;
    constexpr auto default_height = 1080;

    assert(glfwInit());
    glfwSetErrorCallback(error_callback);


    try {
        auto win = std::make_unique<glfw_window>
            (default_width, default_height, "putgame");


        auto next_time = glfwGetTime();

        while (not win->should_close())
        {
            auto time = glfwGetTime();

            if (time >= next_time)
            {
                next_time += 1.0 / 60;

                win->draw();
            }
        }
    } catch (glutils::shader_error e) {
        std::cerr << "shader_error: " << e.log << std::endl;
    }


    glfwTerminate();

    return 0;
}
