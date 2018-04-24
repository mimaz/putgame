/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/res>
#include <putgame/common>
#include <putgame/math>

#include "glass_pieces_view.hxx"

#include "camera.hxx"
#include "glass_pieces.hxx"

namespace
{
    const auto max_count = 12;

    struct extra_data_initializer : std::array<glm::vec2, max_count>
    {
        extra_data_initializer()
        {
            std::default_random_engine gen;
            std::uniform_real_distribution<float> angledis(0, math::pi);

            std::generate(begin(), end(), [&]() -> glm::vec2 {
                auto angle = angledis(gen);

                return glm::vec2(cosf(angle) * 0.5f, sinf(angle) * 0.5f);
            });
        }
    };

    extra_data_initializer extra_data;
}

namespace world
{
    glass_pieces_view::glass_pieces_view(common::context *ctx)
        : cam(ctx->get_part<camera>())
        , vsh(GL_VERTEX_SHADER,
              version_glsl,
              "const lowp int max_count = " + 
              std::to_string(max_count) + ";",
              glass_pieces_vsh)
        , fsh(GL_FRAGMENT_SHADER,
              version_glsl,
              lighting::fragment_source,
              glass_pieces_fsh)
        , pro(&vsh, &fsh)
        , u_extra_v(&pro, "u_extra_v")
        , u_model_v(&pro, "u_model_v")
        , u_view_proj(&pro, "u_view_proj")
        , u_specular_mode(&pro, "u_specular_mode")
        , light(ctx, &pro)
    {}

    void glass_pieces_view::begin()
    {
        glDisable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        pro.use();

        glUniform2fv(u_extra_v, max_count, 
                     glm::value_ptr(extra_data.front()));


        light.calculate();
    }

    void glass_pieces_view::draw(const glass_pieces *pieces)
    {
        u_view_proj = cam->get_view_proj();

        auto matrices = pieces->get_matrices();
        auto index = 0;
        auto total = pieces->get_count();

        while (index < total)
        {
            auto count = std::min(total - index, max_count);

            glUniformMatrix4fv(u_model_v, count,
                               GL_FALSE,
                               glm::value_ptr(matrices[index]));


            u_specular_mode = 0;

            glBlendFunc(GL_ZERO, GL_SRC_COLOR);
            glDrawArraysInstanced(GL_TRIANGLES, 0, 3, count);


            u_specular_mode = 1;

            glBlendFunc(GL_ONE, GL_ONE);
            glDrawArraysInstanced(GL_TRIANGLES, 0, 3, count);


            index += count;
        }
    }

    void glass_pieces_view::end()
    {
    }
}
