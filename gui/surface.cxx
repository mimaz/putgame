/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

/* 
 * touch_event.hxx have to be declared here due 
 * to clang's parsing method
 */
#include "touch_event.hxx"
#include "surface.hxx"

#include "rect_item.hxx"
#include "color_button_view.hxx"

namespace gui
{
    surface::surface(common::context *ctx)
        : object(ctx)
        , dirty_proj(true)
        , width(-1)
        , height(-1)
        , font_builder(text::default_font)
    {
        resize(ctx->get_width(), ctx->get_height());
    }

    surface::~surface()
    {
    }

    void surface::resize(int w, int h)
    {
        if (w != width or h != height)
        {
            width = w;
            height = h;

            dirty_proj = true;

            for (auto item : items)
                item->on_surface_resize(w, h);
        }
    }

    void surface::process()
    {
        for (auto item : items)
            if (item->is_active())
                item->process();

        get<color_button_view>()->mesh_collect();
    }

    void surface::draw()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        for (auto item : items)
            if (item->is_active())
                item->draw();
    }

    void surface::touch(touch_event event)
    {
        for (auto item : items)
            if (item->contains(event.xpos, event.ypos) 
                    or item->is_pressed())
            {
                auto itemev = event;

                itemev.xpos -= item->get_xpos();
                itemev.ypos -= item->get_ypos();

                item->touch(itemev);
            }
    }

    void surface::add_item(rect_item *item)
    {
        items.insert(item);
    }

    void surface::remove_item(rect_item *item)
    {
        items.erase(item);
    }

    int surface::get_width() const
    {
        return width;
    }

    int surface::get_height() const
    {
        return height;
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

    text::font_builder *surface::get_font_builder()
    { return &font_builder; }

    bool surface::comparator::operator()(const rect_item *p, 
                                         const rect_item *q) const
    {
        if (p->get_depth() != q->get_depth())
            return p->get_depth() < q->get_depth();

        return p < q;
    }
}
