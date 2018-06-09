/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/res>

#include "wall_obstacle_view.hxx"

#include "wall_obstacle.hxx"
#include "camera.hxx"
#include "lighting.hxx"

namespace 
{
    constexpr auto max_count = world::wall_obstacle_view::draw_instances;
    constexpr auto side_color = glm::vec3(0.4f, 0.4f, 0.6f);;

    const auto vertex_hdr =
        "const lowp int max_count = " + 
        std::to_string(max_count) +
        ";";

    const auto fragment_hdr =
        "const lowp vec3 side_color = vec3(" +
        std::to_string(side_color.r) +
        ", " +
        std::to_string(side_color.g) +
        ", " +
        std::to_string(side_color.b) +
        ");";
}

namespace world
{
    wall_obstacle_view::wall_obstacle_view(common::context *ctx)
        : cam(ctx->get<camera>())
        , vsh("wall_obstacle_vsh",
              GL_VERTEX_SHADER, 
              version_glsl,
              vertex_hdr,
              wall_obstacle_vsh)
        , fsh("wall_obstacle_fsh",
              GL_FRAGMENT_SHADER, 
              version_glsl,
              fragment_hdr,
              lighting::fragment_source,
              wall_obstacle_fsh)
        , pro("wall_obstacle", &vsh, &fsh)
        , a_coord(&pro, "a_coord")
        , a_normal(&pro, "a_normal")
        , a_tex_coord(&pro, "a_tex_coord")
        , a_mode(&pro, "a_mode")
        , u_model_v(&pro, "u_model_v")
        , u_mvp_v(&pro, "u_mvp_v")
        , u_tex_factor_v(&pro, "u_tex_factor_v")
        , u_texture(&pro, "u_texture")
        , light(ctx, &pro)
    {
        glGenTextures(1, &texhandle);

        glBindTexture(GL_TEXTURE_2D, texhandle);

        glTexParameteri(GL_TEXTURE_2D, 
                        GL_TEXTURE_WRAP_S, 
                        GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, 
                        GL_TEXTURE_WRAP_T, 
                        GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MIN_FILTER,
                        GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MAG_FILTER,
                        GL_NEAREST);

        const GLubyte H = 160, L = 80, A = 255;

        static GLubyte texdata[4][4] = {
            { H, H, L, A }, { L, L, H, A },
            { L, L, H, A }, { H, H, L, A },
        };

        glTexImage2D(GL_TEXTURE_2D, 
                     0,
                     GL_RGBA,
                     2, 2,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     texdata);
    }

    wall_obstacle_view::~wall_obstacle_view()
    {
        glDeleteTextures(1, &texhandle);
    }

    void wall_obstacle_view::begin_drawing()
    {
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        try {
            pro.use();

            a_coord.enable();
            a_normal.enable();
            a_tex_coord.enable();
            a_mode.enable();
        } catch (glutils::location_error er) {
            common::loge("location_error catched: ", er);
        }


        light.calculate();


        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        auto stride = sizeof(float) * 9;

        glVertexAttribPointer(a_coord, 3, GL_FLOAT, GL_FALSE,
                              stride,
                              mesh);

        glVertexAttribPointer(a_normal, 3, GL_FLOAT, GL_FALSE,
                              stride,
                              mesh + 3);

        glVertexAttribPointer(a_tex_coord, 2, GL_FLOAT, GL_FALSE,
                              stride,
                              mesh + 6);

        glVertexAttribPointer(a_mode, 1, GL_FLOAT, GL_FALSE,
                              stride, 
                              mesh + 8);

                              
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texhandle);

        u_texture = 0;

        instance_count = 0;
    }

    void wall_obstacle_view::draw_element(const wall_obstacle *wall)
    {
        auto model = wall->get_model();
        auto tex_factor = glm::vec2(wall->get_width(), wall->get_height());

        models[instance_count] = model;
        mvps[instance_count] = cam->make_mvp(model);
        tex_factors[instance_count] = tex_factor;

        instance_count++;

        if (instance_count == draw_instances)
            draw_walls();
    }

    void wall_obstacle_view::end_drawing()
    {
        if (instance_count > 0)
            draw_walls();

        a_coord.disable();
        a_normal.disable();
        a_tex_coord.disable();
        a_mode.disable();
    }

    void wall_obstacle_view::draw_walls()
    {
        glUniformMatrix4fv(u_model_v, instance_count,
                           GL_FALSE, 
                           glm::value_ptr(models.front()));

        glUniformMatrix4fv(u_mvp_v, instance_count,
                           GL_FALSE, 
                           glm::value_ptr(mvps.front()));

        try {
        glUniform2fv(u_tex_factor_v, instance_count,
                     glm::value_ptr(tex_factors.front()));
        } catch (glutils::location_error er) {
            common::loge("no u_tex_factor_v", er);
        }


        auto vertices = wall_obstacle_view::size_of_mesh / sizeof(float) / 9;


        glDrawArraysInstanced(GL_TRIANGLES, 0, vertices, instance_count);

        instance_count = 0;
    }
}
