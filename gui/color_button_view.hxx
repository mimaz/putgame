/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __gui_color_button_view_hxx
#define __gui_color_button_view_hxx

#include <putgame/common>
#include <putgame/glutils>

namespace gui
{
    class color_button;

    class color_button_view : public common::context::part
    {
    public:
        color_button_view(common::context *ctx);

        void begin();
        void draw(const color_button *btn);
        void end();

    private:
        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;
        glutils::attribute a_coord;
        glutils::uniform u_matrix;
    };
}

#endif
