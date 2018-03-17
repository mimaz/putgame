/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std.hxx>

#include "context.hxx"

#include "trajak.hxx"
#include "visible_object.hxx"
#include "light_box.hxx"

#include "../common/rgb_color.hxx"

namespace world
{
    context::context(int w, int h)
        : width(0), height(0)
    {
        glClearColor(0.0f, 0.2f, 0.0f, 1.0f);
        glCullFace(GL_BACK);

        resize_frame(w, h);

        box = new light_box(this, common::rgb_color::red);
        box->move({ -4, 1, 6 });
    }

    context::~context()
    {
        delete box;

        for (auto obj : vis_objs)
            obj->detach();
    }

    void context::draw_frame()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto obj : vis_objs)
            obj->draw();

        get_part<trajak>()->draw();
    }

    void context::resize_frame(int w, int h)
    {
        width = w;
        height = h;

        glViewport(0, 0, w, h);
    }

    void context::register_object(visible_object *obj)
    {
        vis_objs.insert(obj);
    }

    void context::unregister_object(visible_object *obj)
    {
        vis_objs.erase(obj);
    }
}
