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
#include "world/camera.hxx"

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

    ctx->get_part<world::tunnel>()->set_stripped(true);
    ctx->get_part<world::tunnel>()->set_stripped(false);

    auto cam = ctx->get_part<world::camera>();

    cam->move({ 0, 0, 0 });


    auto box1 = std::make_unique<world::light_box>(
            ctx.get(), world::light_box::blue);

    box1->scale(0.25);
    box1->move({ 0.2, -0.5, 3 });



    auto box2 = std::make_unique<world::light_box>(
            ctx.get(), world::light_box::red);

    box2->scale(0.25);
    box2->move({ 1.5, 0.5, 8 });


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


            try {
                ctx->draw_frame();
            } catch (glutils::location_error e) {
                std::cerr << "location error: " << e.name << std::endl;
            }

            glfwSwapBuffers(win);
            glfwPollEvents();
        }
    } catch (glutils::shader_error e) {
        std::cerr << "shader error: " << e.desc << std::endl;
    }



    glfwDestroyWindow(win);
    glfwTerminate();

    return 0;
}
