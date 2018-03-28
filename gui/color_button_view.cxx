/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/res>

#include "color_button_view.hxx"

#include "color_button.hxx"
#include "surface.hxx"

namespace
{
    constexpr auto max_shadows = 4;

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
              "const lowp int max_shadows = " + 
              std::to_string(max_shadows) + ";",
              color_button_fsh)
        , pro(&vsh, &fsh)
        , a_coord(&pro, "a_coord")
        , u_matrix(&pro, "u_matrix")
        , u_shadows(&pro, "u_shadows")
        , u_shadow_v(&pro, "u_shadow_v")
    {}

    void color_button_view::draw(color_button *btn)
    {
        pro.use();
        a_coord.enable();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(a_coord, 2, GL_FLOAT,
                              GL_FALSE, sizeof(float) * 2,
                              mesh);

        glActiveTexture(GL_TEXTURE0);
        btn->bind_texture();


        u_matrix = get_part<surface>()->get_proj() * btn->get_matrix();

        auto shadows = btn->get_shadows();
        auto count = static_cast<int>(shadows.size());

        glUniform1i(u_shadows, count);
        glUniform4fv(u_shadow_v, count, 
                     glm::value_ptr(shadows.front()));

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


        a_coord.disable();
    }
}
