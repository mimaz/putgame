/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/game>
#include <putgame/math>
#include <putgame/glutils>

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

    struct glfw_application : public game::instance
    {
        static glfw_application *from_window(GLFWwindow *win)
        {
            auto ptr = glfwGetWindowUserPointer(win);

            return static_cast<glfw_application *>(ptr);
        }

        glfw_application() 
            : win(nullptr)
        {
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
            glfwWindowHint(GLFW_CONTEXT_CREATION_API, 
                           GLFW_NATIVE_CONTEXT_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

            win = glfwCreateWindow(1, 1, 
                                   "putgame", 
                                   nullptr,
                                   //glfwGetPrimaryMonitor(),
                                   nullptr);

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

            resize(960, 540);
        }

        ~glfw_application()
        {
            glfwDestroyWindow(win);
        }

        void draw() override
        {
            glfwPollEvents();

            instance::draw();
        }

        void swap_buffers() final
        {
            glfwSwapBuffers(win);
            glfwPollEvents();
        }

        time_t time_millis() final
        {
            return static_cast<time_t>(glfwGetTime() * 1000);
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

                default:
                    break;
            }
        }

        bool should_close()
        {
            return glfwWindowShouldClose(win);
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
                                    double cursorx, 
                                    double cursory)
        {
            auto x = static_cast<int>(cursorx);
            auto y = static_cast<int>(cursory);

            auto ctx = from_window(win);

            ctx->cursor(x, ctx->get_height() - y);
        }

        static void touch_callback(GLFWwindow *win,
                                   int button, int action, int mods)
        {
            auto app = from_window(win);

            if (button == GLFW_MOUSE_BUTTON_LEFT)
            {
                switch (action)
                {
                case GLFW_PRESS:
                    app->press();
                    break;

                case GLFW_RELEASE:
                    app->release();
                    break;
                }
            }
        }


        GLFWwindow *win;
    };
}

int main(int argc, char **argv)
{
    common::logd("dupa");

    if (not glfwInit())
    {
        std::cerr << "intializing GLFW failed" << std::endl;
        return 1;
    }

    glfwSetErrorCallback(error_callback);

    try {
        glfw_application app;
        time_t nexttim = app.time_millis();

        app.start();

        while (not app.should_close())
        {
            app.draw();

            nexttim += 1000 / 40;

            while (not app.should_close() and 
                   app.time_millis() < nexttim)
                std::this_thread::sleep_for
                    (std::chrono::milliseconds(1));
        }

        app.stop();
    } catch (common::invalid_state is) {
        std::cerr << "common::invalid_state " << is.desc << std::endl;
    } catch (glutils::location_error err) {
        std::cerr << "location error: " << err << std::endl; }

    glfwTerminate();

    return 0;
}

