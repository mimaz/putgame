/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __glfw_window_hxx
#define __glfw_window_hxx

#include <putgame/common>

class glfw_window : public common::context
{
public:
    glfw_window(int width, int height,
                const std::string &title = "putgame");

    ~glfw_window();

    void draw();
    bool should_close() const;

private:
    static glfw_window *from_window(GLFWwindow *win);
    static void key_callback(GLFWwindow *win,
                             int key, int code,
                             int action, int mode);
    static void resize_callback(GLFWwindow *win,
                                int width, int height);

    void key(int key, int action);
    void resize(int width, int height);

    GLFWwindow *win;
};

#endif
