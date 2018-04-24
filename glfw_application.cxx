/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/game>
#include <putgame/math>

namespace
{
    void exit_with_error(const std::string &err)
    {
        std::cerr << err << std::endl;

        glfwTerminate();
        exit(1);
    }

    void error_callback(int code, const char *desc)
    {
        exit_with_error(desc);
    }

    class glfw_window : public game::application::window
    {
    public:
        glfw_window(game::application *app) 
            : app(app)
            , win(nullptr)
            , width(1)
            , height(1)
        {
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
            glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

            win = glfwCreateWindow(width, height, 
                                   "putgame", 
                                   nullptr, nullptr);

            if (win == nullptr)
                exit_with_error("creating glfw window failed");


            glfwSetWindowUserPointer(win, this);
            glfwSetKeyCallback(win, key_callback);
            glfwSetWindowSizeCallback(win, resize_callback);
            glfwSetCursorPosCallback(win, cursor_callback);
            glfwSetMouseButtonCallback(win, touch_callback);

            glfwMakeContextCurrent(win);

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glFrontFace(GL_CW);
        }

        ~glfw_window()
        {
            glfwDestroyWindow(win);
        }

        void swap_buffers() override
        {
            glfwSwapBuffers(win);
            glfwPollEvents();

            if (glfwWindowShouldClose(win))
                app->exit();
        }

        time_t get_time_millis() override
        {
            return static_cast<time_t>(glfwGetTime() * 1000);
        }

    private:
        static glfw_window *from_window(GLFWwindow *win)
        {
            auto ptr = glfwGetWindowUserPointer(win);

            return reinterpret_cast<glfw_window *>(ptr);
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

        static void cursor_callback(GLFWwindow *win,
                                          double cursorx, double cursory)
        {
            from_window(win)->cursor(cursorx, cursory);
        }

        static void touch_callback(GLFWwindow *win,
                                         int button, int action, int mods)
        {
            from_window(win)->touch(button, action, mods);
        }

        void key(int key, int action)
        {
            if (action != GLFW_RELEASE)
                return;

            auto angle = math::pi / 20;
            auto step = 0.25f;

            switch (key)
            {
                case GLFW_KEY_ESCAPE:
                    glfwSetWindowShouldClose(win, GLFW_TRUE);
                    break;

                case GLFW_KEY_H:
                    app->move({ -step, 0, 0 });
                    break;

                case GLFW_KEY_J:
                    app->move({ 0, -step, 0 });
                    break;

                case GLFW_KEY_K:
                    app->move({ 0, step, 0 });
                    break;

                case GLFW_KEY_L:
                    app->move({ step, 0, 0 });
                    break;

                case GLFW_KEY_F:
                    app->move({ 0, 0, -step });
                    break;

                case GLFW_KEY_B:
                    app->move({ 0, 0, step });
                    break;

                case GLFW_KEY_A:
                    app->rotate(angle, { 0, 1, 0 });
                    break;

                case GLFW_KEY_D:
                    app->rotate(-angle, { 0, 1, 0 });
                    break;

                case GLFW_KEY_W:
                    app->rotate(angle, { 1, 0, 0 });
                    break;

                case GLFW_KEY_X:
                    app->rotate(-angle, { 1, 0, 0 });
                    break;

                default:
                    break;
            }
        }

        void resize(int w, int h)
        {
            width = w;
            height = h;

            glViewport(0, 0, w, h);

            app->resize(w, h);
        }

        void cursor(double cursorx, double cursory)
        {
            auto xpos = static_cast<int>(cursorx) - width / 2;
            auto ypos = -static_cast<int>(cursory) + height / 2;

            app->cursor(xpos, ypos);
        }

        void touch(int button, int action, int mods)
        {
            if (button == GLFW_MOUSE_BUTTON_LEFT)
            {
                if (action == GLFW_PRESS)
                    app->press();
                else
                    app->release();
            }
        }

    private:
        game::application *app;
        GLFWwindow *win;
        int cursor_xpos, cursor_ypos, width, height;
    };

    class glfw_application : public game::application
    {
        shared_window make_window() override
        {
            return std::make_shared<glfw_window>(this);
        }
    };
}

int glfw_application(int argc, char **argv)
{
    if (not glfwInit())
    {
        std::cerr << "intializing GLFW failed" << std::endl;
        exit(1);
    }

    glfwSetErrorCallback(error_callback);

    {
        class glfw_application app;

        app.run();
    }

    glfwTerminate();

    return 0;
}

