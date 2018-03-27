/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>
#include <putgame/glutils>
#include <putgame/gui>

#include "glfw_window.hxx"

class glfw_window::internal
{
public:
    static internal *from_window(GLFWwindow *win)
    {
        auto ptr = glfwGetWindowUserPointer(win);

        return reinterpret_cast<internal *>(ptr);
    }

    static void key_callback(GLFWwindow *win,
                             int key, int code,
                             int action, int mode)
    {
        from_window(win)->key(key, action);
    }

    static void resize_callback(GLFWwindow *win,
                                int width, int height)
    {
        from_window(win)->resize(width, height);
    }

    internal(int width, int height, const std::string &title)
        : win(nullptr)
        , ctx(nullptr)
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        win = glfwCreateWindow(width, height, title.c_str(), 
                               nullptr, nullptr);
        glfwMakeContextCurrent(win);

        glFrontFace(GL_CW);

        if (win == nullptr)
            throw glfw_window::exception("creating glfw window failed ");

        ctx = std::make_unique<common::context>();

        glfwSetWindowUserPointer(win, this);
        glfwSetKeyCallback(win, key_callback);
        glfwSetWindowSizeCallback(win, resize_callback);

        btn = std::make_unique<gui::color_button>(ctx.get());
    }

    ~internal()
    {
        if (win != nullptr)
            glfwDestroyWindow(win);
    }

    void resize(int width, int height)
    {
        std::cout << "resize: " << width << " x " << height << std::endl;
        glViewport(0, 0, width, height);

        ctx->get_part<gui::surface>()->resize(width, height);
    }

    void key(int key, int action)
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

    void draw()
    {
        try {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            btn->draw();
        } catch (glutils::location_error e) {
            std::cerr << "location error: " << e.name << std::endl;
        }

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    GLFWwindow *win;

    std::unique_ptr<common::context> ctx;
    std::unique_ptr<gui::color_button> btn;
};

glfw_window::glfw_window(int width, int height,
                         const std::string &title)
    : priv(new internal(width, height, title))
{}

glfw_window::~glfw_window()
{
    delete priv;
}

void glfw_window::draw()
{
    priv->draw();
}

bool glfw_window::should_close() const
{
    return glfwWindowShouldClose(priv->win);
}
