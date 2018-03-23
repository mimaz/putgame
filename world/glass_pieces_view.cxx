/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>
#include <putgame-res>

#include "glass_pieces_view.hxx"

#include "context.hxx"
#include "camera.hxx"
#include "glass_pieces.hxx"

namespace
{
    const auto extra_count = 17;

    const float unused_mesh[] = {
        0.0f,
        0.0f,
        0.0f,
    };

    struct extra_data_initializer : std::array<glm::vec2, extra_count>
    {
        extra_data_initializer()
        {
            std::default_random_engine gen;
            std::uniform_real_distribution<float> angledis(0, PI);

            for (auto &v : *this)
            {
                auto angle = angledis(gen);

                v = glm::vec2(sinf(angle) * 0.5f, cosf(angle) * 0.5f);
            }
        }
    };

    extra_data_initializer extra_data;
}

namespace world
{
    glass_pieces_view::glass_pieces_view(context *ctx)
        : cam(ctx->get_part<camera>())
        , vsh(GL_VERTEX_SHADER,
              version_glsl,
              "const lowp int max_extras = " + 
              std::to_string(extra_count) + ";",
              glass_pieces_vsh)
        , fsh(GL_FRAGMENT_SHADER,
              version_glsl,
              lighting::fragment_source,
              glass_pieces_fsh)
        , pro(&vsh, &fsh)
        , u_model_v(&pro, "u_model_v")
        , u_view_proj(&pro, "u_view_proj")
        , u_extra_v(&pro, "u_extra_v")
        , u_specular_mode(&pro, "u_specular_mode")
        , light(ctx, &pro)
    {}

    void glass_pieces_view::begin()
    {
        pro.use();

        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glUniform2fv(u_extra_v, extra_count, 
                     glm::value_ptr(extra_data.front()));


        light.calculate();
    }

    void glass_pieces_view::draw(const glass_pieces *pieces)
    {
        glUniformMatrix4fv(u_model_v, pieces->get_count(),
                           GL_FALSE,
                           glm::value_ptr(*pieces->get_matrices()));


        u_view_proj = cam->get_view_proj();


        u_specular_mode = 0;

        glBlendFunc(GL_ZERO, GL_SRC_COLOR);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 3, pieces->get_count());



        u_specular_mode = 1;

        glBlendFunc(GL_ONE, GL_ONE);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 3, pieces->get_count());
    }

    void glass_pieces_view::end()
    {
    }
}
