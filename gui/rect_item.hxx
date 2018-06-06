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
        static const float strip_mesh[];

        rect_item(common::context *ctx, int depth = 0);
        ~rect_item();

        void set_position(int x, int y);
        void resize(int w, int h);
        void set_active(bool act);

        virtual void draw();
        virtual void process();
        virtual void touch(touch_event event);

        virtual void on_surface_resize(int x, int y);

        bool contains(int x, int y) const;

        int get_xpos() const { return xpos; }
        int get_ypos() const { return ypos; }
        int get_width() const { return width; }
        int get_height() const { return height; }
        int get_depth() const { return depth; }
        bool is_pressed() const { return pressed; }
        bool is_active() const { return active; }

        glm::mat4 get_matrix();
        glm::mat4 get_mvp();

    protected:
        virtual void on_size_changed();

    private:
        int xpos;
        int ypos;
        int width;
        int height;
        int depth;
        bool pressed;
        bool active;

        glm::mat4 matrix;
        bool dirty_matrix;
    };
}

#endif
