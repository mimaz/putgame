/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>
#include <putgame/glutils>
#include <putgame/gui>

#include "glfw_window.hxx"

glfw_window::glfw_window(int width, int height,
                         const std::string &title)
    : win(nullptr)
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    win = glfwCreateWindow(width, height, title.c_str(), 
                           nullptr, nullptr);

    if (win == nullptr)
        throw std::string("creating glfw window failed ");

    glfwSetWindowUserPointer(win, this);
    glfwSetKeyCallback(win, key_callback);
    glfwSetWindowSizeCallback(win, resize_callback);

    glfwMakeContextCurrent(win);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glFrontFace(GL_CW);
}

glfw_window::~glfw_window()
{
    glfwDestroyWindow(win);
}

void glfw_window::draw()
{
    try {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //btn->draw();
    } catch (glutils::location_error e) {
        std::cerr << "location error: " << e.name << std::endl;
    }

    glfwSwapBuffers(win);
    glfwPollEvents();
}

bool glfw_window::should_close() const
{
    return glfwWindowShouldClose(win);
}

glfw_window *glfw_window::from_window(GLFWwindow *win)
{
    auto ptr = glfwGetWindowUserPointer(win);

    return reinterpret_cast<glfw_window *>(ptr);
}

void glfw_window::key_callback(GLFWwindow *win,
                               int key, int code,
                               int action, int mode)
{
    from_window(win)->key(key, action);
}

void glfw_window::resize_callback(GLFWwindow *win,
                                  int width, int height)
{
    from_window(win)->resize(width, height);
}

void glfw_window::key(int key, int action)
{
    if (action != GLFW_RELEASE)
        return;

    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(win, GLFW_TRUE);
            break;

        default:
            break;
    }
}

void glfw_window::resize(int width, int height)
{
    glViewport(0, 0, width, height);

    get_part<gui::surface>()->resize(width, height);
}
