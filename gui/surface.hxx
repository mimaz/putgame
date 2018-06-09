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

    class surface : public common::context::object
    {
    public:
        PUTGAME_OBJECT

        surface(common::context *ctx);
        ~surface();

        void resize(int width, int height);

        void process();
        void draw();
        void touch(touch_event event);

        void add_item(rect_item *item);
        void remove_item(rect_item *item);

        int get_width() const;
        int get_height() const;
        glm::mat4 get_proj() const;

        text::font_builder *get_font_builder();

    private:
        struct comparator
        {
            bool operator()(const rect_item *p, 
                            const rect_item *q) const;
        };

        std::set<rect_item *, comparator> items;

        mutable glm::mat4 proj;
        mutable bool dirty_proj;

        int width;
        int height;

        text::font_builder font_builder;
    };
}

#endif
