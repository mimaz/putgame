/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/res>

#include "color_rectangle_view.hxx"

#include "color_rectangle.hxx"

namespace gui
{
    color_rectangle_view::color_rectangle_view(common::context *ctx)
        : object(ctx)
        , vsh("color_rectangle",
              GL_VERTEX_SHADER,
              version_glsl,
              color_rectangle_vsh)
        , fsh("color_rectangle",
              GL_FRAGMENT_SHADER,
              version_glsl,
              color_rectangle_fsh)
        , pro("color_rectangle", &vsh, &fsh)
        , a_coord(&pro, "a_coord")
        , u_matrix(&pro, "u_matrix")
        , u_color(&pro, "u_color")
    {}

    void color_rectangle_view::draw(color_rectangle *rect)
    {
        pro.use();
        a_coord.enable();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(a_coord, 2, GL_FLOAT,
                              GL_FALSE, sizeof(float) * 2,
                              rect_item::strip_mesh);

        u_matrix = rect->get_mvp();
        u_color = rect->get_color();

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        a_coord.disable();
    }
}
