/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __gui_rect_item_hxx
#define __gui_rect_item_hxx

#include <putgame/common>

#include "touch_event.hxx"

namespace gui
{
    class rect_item : public common::context::object
    {
    public:
        rect_item(common::context *ctx);
        ~rect_item();

        virtual void set_position(int x, int y);
        virtual void resize(int w, int h);

        virtual void draw();
        virtual void process();
        virtual void touch(touch_event event);

        virtual void on_surface_resize(int x, int y);

        bool contains(int x, int y) const;

        int get_xpos() const { return xpos; }
        int get_ypos() const { return ypos; }
        int get_width() const { return width; }
        int get_height() const { return height; }
        bool is_pressed() const { return pressed; }

        glm::mat4 get_matrix();

    protected:
        virtual void on_size_changed();

    private:
        int xpos;
        int ypos;
        int width;
        int height;
        bool pressed;

        glm::mat4 matrix;
        bool dirty_matrix;
    };
}

#endif
