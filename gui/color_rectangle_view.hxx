/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __gui_color_rectangle_view_hxx
#define __gui_color_rectangle_view_hxx

#include <putgame/common>
#include <putgame/glutils>

namespace gui
{
    class color_rectangle;

    class color_rectangle_view : public common::context::object
    {
    public:
        PUTGAME_OBJECT

        color_rectangle_view(common::context *ctx);

        void draw(color_rectangle *rect);

    private:
        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;
        glutils::attribute a_coord;
        glutils::uniform u_matrix;
        glutils::uniform u_color;
    };
}

#endif
