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
    assert(glfwInit());
    glfwSetErrorCallback(error_callback);

    auto win = new glfw_window(1920, 1080, "putgame");

    try {
        auto btn = std::make_unique<gui::color_button>(win);
        btn->resize(400, 400);

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
