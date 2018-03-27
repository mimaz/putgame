/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __glfw_window_hxx
#define __glfw_window_hxx

class glfw_window
{
public:
    class exception;
    class internal;

    glfw_window(int width, int height,
                const std::string &title = "putgame");

    ~glfw_window();

    void draw();

    bool should_close() const;

private:
    internal *priv;
};

class glfw_window::exception
{
public:
    exception(const std::string &desc)
        : desc(desc) {}

    std::string desc;
};

#endif
