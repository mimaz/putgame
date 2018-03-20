/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>
#include <putgame-res>

#include "glass_view.hxx"

#include "glass_pane.hxx"
#include "glass_piece.hxx"
#include "context.hxx"
#include "camera.hxx"

namespace 
{
    const float pane_mesh[] = {
        -0.5f, -0.5f, 
        -0.5f, 0.5f,
        0.5f, 0.5f,

        -0.5f, -0.5f, 
        0.5f, 0.5f,
        0.5f, -0.5f,
    };

    const float piece_mesh[] = {
        // TODO make it better
        -0.5f, -0.5f, 
        -0.5f, 0.5f,
        0.5f, 0.5f,
    };
}

namespace world
{
    glass_view::glass_view(context *ctx)
        : vsh(GL_VERTEX_SHADER, glass_vsh)
        , fsh(GL_FRAGMENT_SHADER, glass_fsh)
        , prog(&vsh, &fsh)
        , a_coord(&prog, "a_coord")
        , u_mvp(&prog, "u_mvp")
        , u_color(&prog, "u_color")
        , cam(ctx->get_part<camera>())
    {}

    void glass_view::begin()
    {
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ZERO, GL_SRC_COLOR);

        prog.use();

        a_coord.enable();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void glass_view::bind_pane()
    {
        glVertexAttribPointer(a_coord, 2, GL_FLOAT,
                              GL_FALSE, sizeof(float) * 2,
                              pane_mesh);
    }

    void glass_view::bind_piece()
    {
        glVertexAttribPointer(a_coord, 2, GL_FLOAT,
                              GL_FALSE, sizeof(float) * 2,
                              piece_mesh);
    }

    void glass_view::draw(const glass_pane *pane)
    {
        u_mvp = cam->make_mvp(pane->get_model());
        u_color = pane->get_color();

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void glass_view::draw(const glass_piece *piece)
    {
        u_mvp = cam->make_mvp(piece->get_model());
        u_color = piece->get_color();

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void glass_view::end()
    {
        a_coord.disable();
    }
}
