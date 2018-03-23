/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "context.hxx"

#include "light_box_manager.hxx"
#include "glass_pane_manager.hxx"
#include "obstacle_manager.hxx"
#include "tunnel_manager.hxx"
#include "camera.hxx"

namespace world
{
    context::context(int w, int h)
        : width(0), height(0)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glFrontFace(GL_CW);

        resize_frame(w, h);
    }

    context::~context()
    {}

    void context::draw_frame()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        get_part<tunnel_manager>()->draw();
        get_part<light_box_manager>()->draw_all();
        get_part<obstacle_manager>()->draw_all();
        get_part<glass_pane_manager>()->draw_all();
    }

    void context::resize_frame(int w, int h)
    {
        width = w;
        height = h;

        glViewport(0, 0, w, h);

        auto ratio = static_cast<float>(w) / h;

        get_part<camera>()->set_view_ratio(ratio);
    }
}
