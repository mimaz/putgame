/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __gui_surface_hxx
#define __gui_surface_hxx

#include <putgame/common>
#include <putgame/text>

#include "touch_event.hxx"

namespace gui
{
    class rect_item;

    class surface : public common::context::part
    {
    public:
        surface(common::context *ctx);
        ~surface();

        void resize(int width, int height);

        void preprocess();
        void touch(touch_event event);

        void add_item(rect_item *item);
        void remove_item(rect_item *item);

        int get_width() const { return width; }
        int get_height() const { return height; }
        glm::mat4 get_proj() const;

        text::font_builder *get_font_builder() 
        { return &font_builder; }

    private:
        std::set<rect_item *> items;

        mutable glm::mat4 proj;
        mutable bool dirty_proj;

        int width;
        int height;

        text::font_builder font_builder;
    };
}

#endif
