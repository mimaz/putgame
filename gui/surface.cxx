/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "surface.hxx"

#include "rect_item.hxx"

namespace gui
{
    surface::surface(common::context *ctx)
        : part(ctx)
        , dirty_proj(true)
        , width(2)
        , height(2)
        , font_builder(text::default_font)
    {}

    surface::~surface()
    {}

    void surface::resize(int w, int h)
    {
        width = w;
        height = h;
        dirty_proj = true;

        for (auto item : items)
            item->on_surface_resize(w, h);
    }

    void surface::preprocess()
    {
        for (auto item : items)
            item->preprocess();
    }

    void surface::touch(touch_event event)
    {
        for (auto item : items)
            if (item->contains(event.xpos, event.ypos) or item->is_pressed())
            {
                auto itemev = event;

                itemev.xpos -= item->get_xpos();
                itemev.ypos -= item->get_ypos();

                item->touch(itemev);
            }
    }

    void surface::draw()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        for (auto item : items)
            item->draw();
    }

    void surface::add_item(rect_item *item)
    {
        items.insert(item);
    }

    void surface::remove_item(rect_item *item)
    {
        items.erase(item);
    }

    glm::mat4 surface::get_proj() const
    {
        if (dirty_proj)
        {
            dirty_proj = false;

            auto w = get_width() / 2.0f;
            auto h = get_height() / 2.0f;

            proj = glm::ortho(-w, w, -h, h);
        }

        return proj;
    }
}
