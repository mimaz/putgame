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

    struct glfw_application : public game::game_instance
    {
        static glfw_application *from_window(GLFWwindow *win)
        {
            auto ptr = glfwGetWindowUserPointer(win);

            return static_cast<glfw_application *>(ptr);
        }

        glfw_application() 
            : win(nullptr)
            , width(960)
            , height(540) 
        {
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
            glfwWindowHint(GLFW_CONTEXT_CREATION_API, 
                           GLFW_NATIVE_CONTEXT_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

            win = glfwCreateWindow(width, height, 
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

            resize(width, height);
        }

        ~glfw_application()
        {
            glfwDestroyWindow(win);
        }

        void draw() final
        {
            glfwPollEvents();

            game_instance::draw();
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

            auto angle = math::pi / 20;
            auto step = 0.25f;

            switch (key)
            {
                case GLFW_KEY_ESCAPE:
                    glfwSetWindowShouldClose(win, GLFW_TRUE);
                    break;

                /*
                case GLFW_KEY_H:
                    move({ -step, 0, 0 });
                    break;

                case GLFW_KEY_J:
                    move({ 0, -step, 0 });
                    break;

                case GLFW_KEY_K:
                    move({ 0, step, 0 });
                    break;

                case GLFW_KEY_L:
                    move({ step, 0, 0 });
                    break;

                case GLFW_KEY_F:
                    move({ 0, 0, -step });
                    break;

                case GLFW_KEY_B:
                    move({ 0, 0, step });
                    break;

                case GLFW_KEY_A:
                    rotate(angle, { 0, 1, 0 });
                    break;

                case GLFW_KEY_D:
                    rotate(-angle, { 0, 1, 0 });
                    break;

                case GLFW_KEY_W:
                    rotate(angle, { 1, 0, 0 });
                    break;

                case GLFW_KEY_X:
                    rotate(-angle, { 1, 0, 0 });
                    break;
                */

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
            auto app = from_window(win);

            auto xpos = static_cast<int>(cursorx)
                - app->get_width() / 2;

            auto ypos = -static_cast<int>(cursory)
                + app->get_height() / 2;

            from_window(win)->cursor(xpos, ypos);
        }

        static void touch_callback(GLFWwindow *win,
                                   int button, int action, int mods)
        {
            auto app = from_window(win);

            if (button == GLFW_MOUSE_BUTTON_LEFT)
            {
                if (action == GLFW_PRESS)
                    app->press();
                else
                    app->release();
            }
        }


        GLFWwindow *win;
        int cursor_xpos, cursor_ypos, width, height;
    };
}

int main(int argc, char **argv)
{
    if (not glfwInit())
    {
        std::cerr << "intializing GLFW failed" << std::endl;
        return 1;
    }

    glfwSetErrorCallback(error_callback);

    {
        glfw_application app;
        time_t nexttim = app.time_millis();

        app.start();

        while (not app.should_close())
        {
            std::cout << "draw!" << std::endl;
            app.draw();

            nexttim += 1000 / 30;

            while (not app.should_close() and 
                   app.time_millis() < nexttim)
                std::this_thread::sleep_for
                    (std::chrono::milliseconds(1));
        }

        app.stop();
    }

    glfwTerminate();

    return 0;
}

