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
    class surface;
    class buffered_text;

    class color_button_view : public common::context::part
    {
    public:
        static constexpr auto max_shadows = 1;

        color_button_view(common::context *ctx);

        void draw(color_button *btn);

    private:
        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;
        glutils::attribute a_coord;
        glutils::uniform u_matrix;
        glutils::uniform u_shadows;
        glutils::uniform u_exposure_v;
        glutils::uniform u_origin_v;

        std::array<glm::vec2, max_shadows> exposures;
        std::array<glm::vec2, max_shadows> origins;
    };
}

#endif
