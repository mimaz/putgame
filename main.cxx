/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "world/context.hxx"
#include "world/trajak.hxx"
#include "world/tunnel.hxx"
#include "world/tunnel_mesh.hxx"
#include "world/light_box.hxx"
#include "world/tunnel_path.hxx"

#include "glutils/exception.hxx"

static void error_callback(int code, const char *desc)
{
    std::cerr << "GLFW error: " << code << ": " << desc << std::endl;
    exit(1);
}

static void key_callback(GLFWwindow *win, 
                         int key, int code, 
                         int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(win, GLFW_TRUE);
}

static void resize_callback(GLFWwindow *win,
                            int width, int height)
{
    std::cout << "resize: " << width << " x " << height << std::endl;

    auto ctxptr = glfwGetWindowUserPointer(win);
    auto ctx = reinterpret_cast<world::context *>(ctxptr);

    ctx->resize_frame(width, height);
}

int main(void)
{
    constexpr auto default_width = 640;
    constexpr auto default_height = 480;

    assert(glfwInit());

    glfwSetErrorCallback(error_callback);


    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
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


    auto ctx = std::make_unique<world::context>(default_width, default_height);

    ctx->get_part<world::tunnel_path>();

    auto box = std::make_unique<world::light_box>(
            ctx.get(), world::light_box::green);

    box->move({ -3, 2, 6 });


    glfwSetWindowUserPointer(win, ctx.get());


    double next_time = glfwGetTime();

    try {
        while (!glfwWindowShouldClose(win))
        {
            double time = glfwGetTime();

            if (time < next_time)
                // TODO sleep?
                continue;

            next_time += 1.0 / 60;


            ctx->draw_frame();


            glfwSwapBuffers(win);
            glfwPollEvents();
        }
    } catch (glutils::shader_error e) {
        std::cerr << "error: " << e.desc << std::endl;
    } catch (glutils::location_error e) {
        std::cerr << "error: " << e.name << std::endl;
    }




    glfwDestroyWindow(win);
    glfwTerminate();

    return 0;
}
