/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>
#include <putgame/glutils>
#include <putgame/gui>
#include <putgame/world>

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
    glfwSetCursorPosCallback(win, cursor_callback);
    glfwSetMouseButtonCallback(win, touch_callback);

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

        get_part<world::draw_manager>()->draw_all();

        get_part<gui::surface>()->preprocess();
        get_part<gui::surface>()->draw();
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

void glfw_window::cursor_callback(GLFWwindow *win,
                                  double cursorx, double cursory)
{
    from_window(win)->cursor(cursorx, cursory);
}

void glfw_window::touch_callback(GLFWwindow *win,
                                 int button, int action, int mods)
{
    from_window(win)->touch(button, action, mods);
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

void glfw_window::resize(int w, int h)
{
    width = w;
    height = h;

    glViewport(0, 0, w, h);

    auto ratio = static_cast<float>(w) / h;

    get_part<gui::surface>()->resize(w, h);
    get_part<world::camera>()->set_view_ratio(ratio);
}

void glfw_window::cursor(double cursorx, double cursory)
{
    cursor_xpos = static_cast<int>(cursorx) - width / 2;
    cursor_ypos = static_cast<int>(cursory) - height / 2;

    gui::touch_event event(gui::touch_event::move, 
                           cursor_xpos, cursor_ypos);

    get_part<gui::surface>()->touch(event);
}

void glfw_window::touch(int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        gui::touch_event::event_type type;

        if (action == GLFW_PRESS)
            type = gui::touch_event::press;
        else
            type = gui::touch_event::release;

        gui::touch_event event(type, cursor_xpos, cursor_ypos);

        get_part<gui::surface>()->touch(event);
    }
}
