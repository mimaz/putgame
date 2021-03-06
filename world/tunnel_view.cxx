/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/res>
#include <putgame/common>
#include <putgame/math>

#include "tunnel_view.hxx"

#include "way_path.hxx"
#include "camera.hxx"
#include "lighting.hxx"
#include "constants.hxx"

namespace
{
    std::string vsh_header(int max_count)
    {
        return "const mediump int max_count = " +
               std::to_string(max_count) +
               ";\n";
    }
}

namespace world
{
    tunnel_view::tunnel_view(common::context *ctx)
        : object(ctx)
        , mesh(tunnel_quality, tunnel_width)
        , path(ctx, mesh.get_gap())
        , light(ctx, &prog)
        , cam(ctx->get<camera>())
        , vsh("tunnel_vsh",
              GL_VERTEX_SHADER, 
              version_glsl,
              vsh_header(max_count),
              tunnel_vsh)
        , fsh("tunnel_fsh",
              GL_FRAGMENT_SHADER, 
              version_glsl,
              world::lighting::fragment_source,
              tunnel_fsh)
        , prog("tunnel", &vsh, &fsh)
        , a_coord(&prog, "a_coord")
        , u_model_v(&prog, "u_model_v")
        , u_mvp_v(&prog, "u_mvp_v")
        , u_hash_v(&prog, "u_hash_v")
        , vbo(GL_ARRAY_BUFFER, mesh.get_vertex_ptr(), 
              mesh.get_vertex_data_size())
        , ibo(GL_ELEMENT_ARRAY_BUFFER, mesh.get_index_ptr(),
              mesh.get_index_count())
    {}

    void tunnel_view::draw()
    {
        begin_drawing();

        for (auto &pt : path.points())
            draw(pt);

        end_drawing();
    }

    void tunnel_view::begin_drawing()
    {
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);

        prog.use();

        a_coord.enable();


        light.calculate();


        vbo.bind();
        ibo.bind();

        glVertexAttribPointer(a_coord, 2, GL_FLOAT,
                              GL_FALSE,
                              sizeof(float) * 2,
                              nullptr);

        count = 0;
    }

    void tunnel_view::draw(const path_point &pt)
    {
        auto angle = -math::pi / mesh.get_quality() * pt.index();
        auto axis = glm::vec3(0, 0, 1);

        auto matrix = pt.matrix() * glm::rotate(angle, axis);

        models[count] = matrix;
        mvps[count] = cam->make_mvp(matrix);
        hashes[count] = std::hash<GLint>()(pt.index()) % 100;

        count++;

        if (count == max_count)
            draw_segments();
    }

    void tunnel_view::end_drawing()
    {
        if (count > 1)
            draw_segments();

        a_coord.disable();
    }

    void tunnel_view::draw_segments()
    {
        glUniformMatrix4fv(u_model_v, count, GL_FALSE, 
                           glm::value_ptr(models.front()));

        glUniformMatrix4fv(u_mvp_v, count, GL_FALSE, 
                           glm::value_ptr(mvps.front()));

        glUniform1iv(u_hash_v, count, &hashes.front());

        glDrawElementsInstanced(GL_TRIANGLES, mesh.get_index_count(),
                                GL_UNSIGNED_BYTE, nullptr, count - 1);

        models[0] = models.back();
        mvps[0] = mvps.back();
        hashes[0] = hashes.back();

        count = 1;
    }
}
