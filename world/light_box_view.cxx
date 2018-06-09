/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/res>

#include <putgame/common>

#include "light_box_view.hxx"

#include "light_box.hxx"
#include "camera.hxx"

constexpr auto boxes_per_draw = world::light_box_view::boxes_per_draw;

namespace world
{
    light_box_view::light_box_view(common::context *ctx)
        : vsh("light_box_vsh",
              GL_VERTEX_SHADER, 
              version_glsl,
              "const lowp int max_count = " +
              std::to_string(::boxes_per_draw) + ";",
              light_box_vsh)
        , fsh("light_box_fsh",
              GL_FRAGMENT_SHADER,
              version_glsl,
              lighting::fragment_source,
              light_box_fsh)
        , prog("light_box", &vsh, &fsh)
        , a_coord(&prog, "a_coord")
        , a_normal(&prog, "a_normal")
        , u_type(&prog, "u_type")
        , u_model_v(&prog, "u_model_v")
        , u_mvp_v(&prog, "u_mvp_v")
        , u_color_v(&prog, "u_color_v")
        , vbo(GL_ARRAY_BUFFER, 
              mesh, size_of_mesh)
        , light(ctx, &prog)
        , cam(ctx->get<camera>())
    {}

    void light_box_view::begin_drawing()
    {
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);



        prog.use();
        vbo.bind();

        light.calculate();

        auto offset = [](int n) -> void * {
            return reinterpret_cast<void *>(n * sizeof(GLfloat));
        };

        auto stride = sizeof(GLfloat) * 6;

        a_coord.enable();
        a_normal.enable();

        glVertexAttribPointer(a_coord, 3, GL_FLOAT,
                              GL_FALSE, stride,
                              offset(0));
        glVertexAttribPointer(a_normal, 3, GL_FLOAT,
                              GL_FALSE, stride,
                              offset(3));

        count = 0;
    }

    void light_box_view::draw_element(const light_box *box)
    {
        models[count] = box->get_model();
        mvps[count] = cam->make_mvp(box->get_model());
        colors[count] = box->get_surface_color();

        count++;

        if (count == boxes_per_draw)
            draw_instances();
    }

    void light_box_view::end_drawing()
    {
        if (count > 0)
            draw_instances();

        a_coord.disable();
        a_normal.disable();
    }

    void light_box_view::draw_instances()
    {
        glUniformMatrix4fv(u_model_v, count, GL_FALSE, 
                           glm::value_ptr(models.front()));
        glUniformMatrix4fv(u_mvp_v, count, GL_FALSE, 
                           glm::value_ptr(mvps.front()));
        glUniform3fv(u_color_v, count, 
                     glm::value_ptr(colors.front()));


        u_type = 0;
        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, count);

        u_type = 1;
        glDrawArraysInstanced(GL_TRIANGLES, 36, 24, count);

        u_type = 2;
        glDrawArraysInstanced(GL_TRIANGLES, 60, 72, count);

        count = 0;
    }
}
