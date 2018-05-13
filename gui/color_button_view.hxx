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

    class color_button_view : public common::context::object
    {
    public:
        color_button_view(common::context *ctx);

        void draw(color_button *btn);

    private:
        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;
        glutils::attribute a_coord;
        glutils::uniform u_matrix;
        glutils::uniform u_primary_color;
        glutils::uniform u_secondary_color;
        glutils::uniform u_ratio;
        glutils::uniform u_shadows;
        glutils::uniform u_shadow_v;
    };
}

#endif
