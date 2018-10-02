/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/res>

#include "color_button_view.hxx"

#include "color_button.hxx"
#include "surface.hxx"

namespace gui
{
    namespace 
    {
        constexpr auto max_shadows = 3;

        int button_hash(color_button *btn)
        {
            return (btn->get_width() << 16)  + btn->get_height();
        }
    }

    class color_button_mesh
    {
    public:
        std::array<float, 12> data;
        bool used;

        color_button_mesh(color_button *btn)
            : used(false)
        {
            auto w = static_cast<float>(btn->get_width());
            auto h = static_cast<float>(btn->get_height());

            auto margin = std::min(w, h) / 8;

            auto make = [margin](int dim, float factor) -> float {
                return 0.5f - factor * margin / dim;
            };

            auto x_far = make(w, 1);
            auto y_far = make(h, 1);
            auto x_near = make(w, 2);
            auto y_near = make(h, 2);

            data[0] = -x_near;
            data[1] = y_far;

            data[2] = -x_far;
            data[3] = y_near;

            data[4] = x_far;
            data[5] = y_far;

            data[6] = -x_far;
            data[7] = -y_far;

            data[8] = x_far;
            data[9] = -y_near;

            data[10] = x_near;
            data[11] = -y_far;
        }

        bool is_used()
        {
            return used;
        }

        const void *memory()
        {
            used = true;
            return data.data();
        }
    };

    color_button_view::color_button_view(common::context *ctx)
        : object(ctx)
        , vsh("textured_rect_vsh",
              GL_VERTEX_SHADER,
              version_glsl,
              textured_rect_vsh)
        , fsh("color_button_fsh",
              GL_FRAGMENT_SHADER,
              version_glsl,
              "const lowp int max_shadows = " + 
              std::to_string(max_shadows) + ";",
              color_button_fsh)
        , pro("color_button", &vsh, &fsh)
        , a_coord(&pro, "a_coord")
        , u_matrix(&pro, "u_matrix")
        , u_primary_color(&pro, "u_primary_color")
        , u_secondary_color(&pro, "u_secondary_color")
        , u_ratio(&pro, "u_ratio")
        , u_shadows(&pro, "u_shadows")
        , u_shadow_v(&pro, "u_shadow_v")
    {}

    void color_button_view::draw(color_button *btn)
    {
        pro.use();
        a_coord.enable();

        auto hash = button_hash(btn);
        auto mesh = mesh_map[hash];

        if (mesh == nullptr)
            mesh_map[hash] = mesh = std::make_shared<color_button_mesh>(btn);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(a_coord, 2, GL_FLOAT,
                              GL_FALSE, sizeof(float) * 2,
                              mesh->memory());

        glActiveTexture(GL_TEXTURE0);
        btn->bind_texture();


        u_matrix = btn->get_mvp();

        auto shadows = btn->get_shadows();
        auto count = std::min(static_cast<int>(shadows.size()), max_shadows);

        u_primary_color = btn->get_primary_color();
        u_secondary_color = btn->get_secondary_color();
        u_ratio = static_cast<float>(btn->get_width()) / btn->get_height();

        u_shadows = count;

        glUniform4fv(u_shadow_v, count, 
                     glm::value_ptr(shadows.front()));

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);


        a_coord.disable();
    }

    void color_button_view::mesh_collect()
    {
        std::vector<int> toremove;

        for (auto e : mesh_map)
            toremove.push_back(e.first);

        for (auto i : toremove)
            mesh_map.erase(i);
    }
}
