/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __gui_rect_item_hxx
#define __gui_rect_item_hxx

#include <putgame/common>

namespace gui
{
    class rect_item : public common::context::object
    {
    public:
        rect_item(common::context *ctx);

        void set_position(int x, int y);
        void set_size(int w, int h);

        virtual void draw() = 0;

        int get_xpos() const { return xpos; }
        int get_ypos() const { return ypos; }
        int get_width() const { return width; }
        int get_height() const { return height; }

        glm::mat4 get_matrix();

    protected:
        virtual void on_size_changed();

    private:
        int xpos;
        int ypos;
        int width;
        int height;

        glm::mat4 matrix;
        bool dirty_matrix;
    };
}

#endif
