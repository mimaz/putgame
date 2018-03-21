/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>
#include <putgame-res>

#include "wall_obstacle_view.hxx"

#include "wall_obstacle.hxx"
#include "context.hxx"
#include "camera.hxx"
#include "lighting.hxx"

namespace 
{
    const auto dim = 0.25f;
    const auto bri = 0.75f;

    const float texdata[] = {
        dim, dim, dim, bri, bri, dim,
        bri, bri, dim, dim, dim, dim,
    };
}

namespace world
{
    wall_obstacle_view::wall_obstacle_view(context *ctx)
        : cam(ctx->get_part<camera>())
        , vsh(GL_VERTEX_SHADER, wall_obstacle_vsh)
        , fsh(GL_FRAGMENT_SHADER, 
              lighting_fsh,
              wall_obstacle_fsh)
        , pro(&vsh, &fsh)
        , a_coord(&pro, "a_coord")
        , a_normal(&pro, "a_normal")
        , a_tex_coord(&pro, "a_tex_coord")
        , a_mode(&pro, "a_mode")
        , u_model(&pro, "u_model")
        , u_mvp(&pro, "u_mvp")
        , u_tex_factor(&pro, "u_tex_factor")
        , light(std::make_shared<lighting>(ctx, &pro))
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

        glTexImage2D(GL_TEXTURE_2D, 0,
                     GL_RGB,
                     2, 2,
                     0,
                     GL_RGB,
                     GL_FLOAT,
                     texdata);
    }

    wall_obstacle_view::~wall_obstacle_view()
    {
        glDeleteTextures(1, &texhandle);
    }

    void wall_obstacle_view::begin()
    {
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        pro.use();

        a_coord.enable();
        a_normal.enable();
        a_tex_coord.enable();
        a_mode.enable();


        light->calculate();


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

                              
        glBindTexture(GL_TEXTURE_2D, texhandle);
    }

    void wall_obstacle_view::draw(const wall_obstacle *wall)
    {
        auto model = wall->get_model();
        auto tex_factor = glm::vec2(wall->get_width(), wall->get_height());

        u_model = model;
        u_mvp = cam->make_mvp(model);
        u_tex_factor = tex_factor;

        auto vertices = wall_obstacle_view::size_of_mesh / sizeof(float) / 9;

        glDrawArrays(GL_TRIANGLES, 0, vertices);
    }

    void wall_obstacle_view::end()
    {
        a_coord.disable();
        a_normal.disable();
        a_tex_coord.disable();
        a_mode.disable();
    }
}
