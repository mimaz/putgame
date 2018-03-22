/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "common/rgb_color.hxx"

#include "world/context.hxx"
#include "world/tunnel.hxx"
#include "world/tunnel_mesh.hxx"
#include "world/way_path.hxx"
#include "world/light_box.hxx"
#include "world/camera.hxx"
#include "world/glass_pane.hxx"
#include "world/glass_piece.hxx"
#include "world/wall_obstacle.hxx"

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
    auto ctxptr = glfwGetWindowUserPointer(win);
    auto ctx = reinterpret_cast<world::context *>(ctxptr);
    auto cam = ctx->get_part<world::camera>();


    if (action != GLFW_RELEASE)
        return;

    auto angle = PI / 20;
    auto step = 0.25f;

    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(win, GLFW_TRUE);
            break;

        case GLFW_KEY_H:
            cam->move({ -step, 0, 0 });
            break;

        case GLFW_KEY_J:
            cam->move({ 0, -step, 0 });
            break;

        case GLFW_KEY_K:
            cam->move({ 0, step, 0 });
            break;

        case GLFW_KEY_L:
            cam->move({ step, 0, 0 });
            break;

        case GLFW_KEY_F:
            cam->move({ 0, 0, -step });
            break;

        case GLFW_KEY_B:
            cam->move({ 0, 0, step });
            break;

        case GLFW_KEY_A:
            cam->rotate(angle, { 0, 1, 0 });
            break;

        case GLFW_KEY_D:
            cam->rotate(-angle, { 0, 1, 0 });
            break;

        case GLFW_KEY_W:
            cam->rotate(angle, { 1, 0, 0 });
            break;

        case GLFW_KEY_X:
            cam->rotate(-angle, { 1, 0, 0 });
            break;
    }
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


    auto ctx = std::make_unique<world::context>(default_width, default_height);

    for (int i = 0; i < 100; i++)
        ctx->get_part<world::way_path>()->generate();

    ctx->get_part<world::tunnel>()->set_stripped(false);

    auto cam = ctx->get_part<world::camera>();

    cam->move({ 0, 0, -1 });


    auto wall = std::make_unique<world::wall_obstacle>(
            ctx.get(), 2, 5);

    wall->move({ 0, 0, 3 });


    auto box1 = std::make_unique<world::light_box>(
            ctx.get(), world::light_box::blue);

    box1->scale(0.25);
    box1->move({ 0.2, -0.5, 3 });



    auto box2 = std::make_unique<world::light_box>(
            ctx.get(), world::light_box::red);

    box2->scale(0.25);
    box2->move({ 1.3, 0.4, 8 });



    auto pane = std::make_unique<world::glass_pane>(
            ctx.get(), common::rgb_color::green, glm::vec2(1, 1));

    pane->move({ 0, 0, 4 });

    auto piece = std::make_unique<world::glass_piece>(pane.get());

    piece->move({ 0.3, 0, 6 });


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
        std::cerr << e.code << std::endl
                  << "shader error: " << e.log << std::endl;
    }



    glfwDestroyWindow(win);
    glfwTerminate();

    return 0;
}
