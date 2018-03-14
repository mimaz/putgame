/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std.hxx>

static void error_callback(int code, const char *desc)
{
    std::cerr << "GLFW error: " << code << ": " << desc << std::endl;
    abort();
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
}

int main(void)
{
    assert(glfwInit());

    glfwSetErrorCallback(error_callback);


    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow *win = glfwCreateWindow(640, 480, "putgame", nullptr, nullptr);

    if (win == nullptr)
    {
        std::cerr << "creating window failed!" << std::endl;

        glfwTerminate();
        return 1;
    }


    glfwSetKeyCallback(win, key_callback);
    glfwSetFramebufferSizeCallback(win, resize_callback);

    glfwMakeContextCurrent(win);


    double next_time = glfwGetTime();

    while (!glfwWindowShouldClose(win))
    {
        double time = glfwGetTime();

        if (time < next_time)
            // TODO sleep?
            continue;

        next_time += 1.0 / 60;


        glfwSwapBuffers(win);
        glfwPollEvents();
    }




    glfwDestroyWindow(win);
    glfwTerminate();

    return 0;
}
