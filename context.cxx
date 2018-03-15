/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std.hxx>

#include "context.hxx"
#include "trajak.hxx"

namespace world
{
    context::context(int w, int h)
        : width(0), height(0)
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        resize_frame(w, h);
    }

    context::~context()
    {}

    void context::draw_frame()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        get_part<trajak>()->draw();
    }

    void context::resize_frame(int w, int h)
    {
        width = w;
        height = h;

        glViewport(0, 0, w, h);
    }
}
