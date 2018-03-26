/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/res>

#include "color_button_view.hxx"

namespace
{
    const float mesh[] = {
        -0.5f, 0.5f,
        0.5f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f,
    };
}

namespace gui
{
    color_button_view::color_button_view(common::context *ctx)
        : part(ctx)
        , vsh(GL_VERTEX_SHADER,
              version_glsl,
              textured_rect_vsh)
        , fsh(GL_FRAGMENT_SHADER,
              version_glsl,
              color_button_fsh)
        , pro(&vsh, &fsh)
        , a_coord(&pro, "a_coord")
        , u_matrix(&pro, "u_matrix")
    {}

    void color_button_view::begin()
    {
        pro.use();
        a_coord.enable();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(a_coord, 2, GL_FLOAT,
                              GL_FALSE, sizeof(float) * 2,
                              mesh);
    }

    void color_button_view::draw(const color_button *btn)
    {
        // TODO
    }

    void color_button_view::end()
    {
        a_coord.disable();
    }
}
