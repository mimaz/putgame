/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>
#include <putgame/text>
#include <putgame/glutils>

#include "test.hxx"

static void error_callback(int code, const char *desc)
{
    std::cerr << "GLFW error: " << code << ": " << desc << std::endl;
    exit(1);
}

static void key_callback(GLFWwindow *win, 
                         int key, int code, 
                         int action, int mode)
{
    if (action != GLFW_RELEASE)
        return;

    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(win, GLFW_TRUE);
            break;
    }
}

static void resize_callback(GLFWwindow *win,
                            int width, int height)
{
    std::cout << "resize: " << width << " x " << height << std::endl;
    glViewport(0, 0, width, height);
}

int main(void)
{
    constexpr auto default_width = 1920;
    constexpr auto default_height = 1080;

    assert(glfwInit());

    glfwSetErrorCallback(error_callback);


    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow *win = glfwCreateWindow(default_width, default_height,
                                       "putgame", nullptr, nullptr);


    if (win == nullptr)
    {
        std::cerr << "creating window failed!" << std::endl;

        glfwTerminate();
        return 1;
    }


    glfwSetKeyCallback(win, key_callback);
    glfwSetFramebufferSizeCallback(win, resize_callback);

    glfwMakeContextCurrent(win);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glFrontFace(GL_CW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    try {
        auto ctx = std::make_unique<common::context>();
        auto font = std::make_unique<text::font_builder>();
        auto capt = std::make_unique<text::text_buffer>(ctx.get(), font.get());

        capt->set_width(512);
        capt->set_height(512);
        capt->set_font_size(100, 100);


        auto tst = std::make_unique<test>();


        double next_time = glfwGetTime();

        while (!glfwWindowShouldClose(win))
        {
            double time = glfwGetTime();

            if (time < next_time)
                // TODO sleep?
                continue;

            next_time += 1.0 / 60;


            try {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                tst->draw(capt->get_texture_handle());
            } catch (glutils::location_error e) {
                std::cerr << "location error: " << e.name << std::endl;
            }

            glfwSwapBuffers(win);
            glfwPollEvents();
        }
    } catch (glutils::shader_error e) {
        std::cerr << "shader_error: " << e.log << std::endl;
    }

    glfwDestroyWindow(win);
    glfwTerminate();

    return 0;
}
