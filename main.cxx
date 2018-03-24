/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>
#include <putgame/text>

#include "world/context.hxx"
#include "world/tunnel_mesh.hxx"
#include "world/way_path.hxx"
#include "world/light_box.hxx"
#include "world/camera.hxx"
#include "world/glass_pane.hxx"
#include "world/glass_pieces.hxx"
#include "world/draw_manager.hxx"
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

    //ctx->resize_frame(width, height);

    glViewport(0, 0, width, height);
    
    auto ratio = static_cast<float>(width) / height;
    ctx->get_part<world::camera>()->set_view_ratio(ratio);
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


    text::font_builder::character_recipe recipe = {
        { { 0, 0 } },
        {},
        0
    };

    try {
        auto font = std::make_unique<text::font_builder>(&recipe, 1);
    } catch (glutils::shader_error e) {
        std::cout << "shader error: " << e.log << std::endl;
    } catch (glutils::location_error e) {
        std::cout << "location error: " << e.name << std::endl;
    }


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glFrontFace(GL_CW);


    auto ctx = std::make_unique<world::context>();

    for (int i = 0; i < 100; i++)
        ctx->get_part<world::way_path>()->generate();


    auto cam = ctx->get_part<world::camera>();

    cam->move(0, 0, 1);


    auto wall = std::make_unique<world::wall_obstacle>(
            ctx.get(), 2, 5);

    wall->translate(0, 0, -1);


    auto box1 = std::make_unique<world::light_box>(
            ctx.get(), world::light_box::blue);

    box1->translate(-0.2, -0.5, -3);
    box1->scale(0.25);



    auto box2 = std::make_unique<world::light_box>(
            ctx.get(), world::light_box::red);

    box2->translate(-0.3, 0.4, -4);
    box2->scale(0.25);



    auto pane = std::make_unique<world::glass_pane>(
            ctx.get(), common::green(), glm::vec2(2, 2));

    pane->translate(0, 0, -2);


    auto pieces = std::make_unique<world::glass_pieces>(
            pane.get());


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
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                ctx->get_part<world::draw_manager>()->draw_all();
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
