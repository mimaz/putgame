/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/res>

#include "glass_pane_view.hxx"

#include "camera.hxx"
#include "glass_pane.hxx"

namespace 
{
    const float mesh[] = {
        -0.5f, -0.5f,
        -0.5f, 0.5f,
        0.5f, 0.5f,

        -0.5f, -0.5f,
        0.5f, 0.5f,
        0.5f, -0.5f,
    };
}

constexpr auto instances_per_call = world::glass_pane_view::instances_per_call;

namespace world
{
    glass_pane_view::glass_pane_view(common::context *ctx)
        : cam(ctx->get<camera>())
        , vsh("glass_pane_vsh",
              GL_VERTEX_SHADER,
              version_glsl,
              "const lowp int max_count = " + 
              std::to_string(::instances_per_call) + ";",
              glass_pane_vsh)
        , fsh("glass_pane_fsh",
              GL_FRAGMENT_SHADER,
              version_glsl,
              lighting::fragment_source,
              glass_common_fsh,
              glass_pane_fsh)
        , pro("glass_pane", &vsh, &fsh)
        , a_coord(&pro, "a_coord")
        , u_model_v(&pro, "u_model_v")
        , u_mvp_v(&pro, "u_mvp_v")
        , u_color_v(&pro, "u_color_v")
        , u_specular_mode(&pro, "u_specular_mode")
        , vbo(GL_ARRAY_BUFFER, mesh, sizeof(mesh))
        , light(ctx, &pro)
    {}

    void glass_pane_view::begin_drawing()
    {
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);

        pro.use();
        a_coord.enable();

        vbo.bind();

        glVertexAttribPointer(a_coord, 2, GL_FLOAT,
                              GL_FALSE, sizeof(float) * 2,
                              nullptr);

        light.calculate();

        instance_count = 0;
    }

    void glass_pane_view::draw_element(const glass_pane *pane)
    {
        models[instance_count] = pane->get_model();
        mvps[instance_count] = cam->make_mvp(pane->get_model());
        colors[instance_count] = pane->get_color();

        instance_count++;

        if (instance_count == instances_per_call)
            draw();
    }

    void glass_pane_view::end_drawing()
    {
        if (instance_count > 0)
            draw();

        a_coord.disable();
    }

    void glass_pane_view::draw()
    {
        glUniformMatrix4fv(u_model_v, instance_count,
                           GL_FALSE,
                           glm::value_ptr(models.front()));
        glUniformMatrix4fv(u_mvp_v, instance_count,
                           GL_FALSE,
                           glm::value_ptr(mvps.front()));
        glUniform3fv(u_color_v, instance_count,
                     glm::value_ptr(colors.front()));


        u_specular_mode = 0;

        glDepthFunc(GL_LESS);
        glBlendFunc(GL_ZERO, GL_SRC_COLOR);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, instance_count);

        u_specular_mode = 1;

        glDepthFunc(GL_LEQUAL);
        glBlendFunc(GL_ONE, GL_ONE);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, instance_count);


        instance_count = 0;
    }
}
