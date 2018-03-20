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
#include "lighting.hxx"

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
        , fsh_tr(GL_FRAGMENT_SHADER, 
                 lighting_fsh,
                 glass_transparency_fsh)
        , prog_tr(&vsh, &fsh_tr)
        , a_coord_tr(&prog_tr, "a_coord")
        , u_mvp_tr(&prog_tr, "u_mvp")
        , u_color_tr(&prog_tr, "u_color")
        , fsh_sp(GL_FRAGMENT_SHADER, 
                 lighting_fsh,
                 glass_specular_fsh)
        , prog_sp(&vsh, &fsh_sp)
        , a_coord_sp(&prog_sp, "a_coord")
        , u_model_sp(&prog_sp, "u_model")
        , u_mvp_sp(&prog_sp, "u_mvp")
        , light(std::make_shared<lighting>(ctx, &prog_sp))
        , cam(ctx->get_part<camera>())
    {}

    void glass_view::begin(bool specular)
    {
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);

        if (specular)
        {
            glBlendFunc(GL_ONE, GL_ONE);
            glDisable(GL_DEPTH_TEST);

            prog_sp.use();
            a_coord_sp.enable();

            light->calculate();
        }
        else
        {
            glBlendFunc(GL_ZERO, GL_SRC_COLOR);

            prog_tr.use();
            a_coord_tr.enable();
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void glass_view::bind_pane(bool specular)
    {
        auto &coord = specular ? a_coord_sp : a_coord_tr;

        glVertexAttribPointer(coord, 2, GL_FLOAT,
                              GL_FALSE, sizeof(float) * 2,
                              pane_mesh);
    }

    void glass_view::bind_piece(bool specular)
    {
        auto &coord = specular ? a_coord_sp : a_coord_tr;

        glVertexAttribPointer(coord, 2, GL_FLOAT,
                              GL_FALSE, sizeof(float) * 2,
                              piece_mesh);
    }

    void glass_view::draw(const glass_pane *pane, 
                          bool specular)
    {
        if (specular)
        {
            u_model_sp = pane->get_model();
            u_mvp_sp = cam->make_mvp(pane->get_model());
        }
        else
        {
            u_mvp_tr = cam->make_mvp(pane->get_model());
            u_color_tr = pane->get_color();
        }

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void glass_view::draw(const glass_piece *piece,
                          bool specular)
    {
        if (specular)
        {
            u_model_sp = piece->get_model();
            u_mvp_sp = cam->make_mvp(piece->get_model());
        }
        else
        {
            u_mvp_tr = cam->make_mvp(piece->get_model());
            u_color_tr = piece->get_color();
        }

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void glass_view::end(bool specular)
    {
        if (specular)
            a_coord_sp.disable();
        else
            a_coord_tr.disable();
    }
}
