/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>
#include <putgame-res>

#include <common/rgb_color.hxx>
#include <common/exception.hxx>

#include "light_box_view.hxx"

#include "light_box.hxx"
#include "context.hxx"
#include "camera.hxx"

namespace world
{
    light_box_view::light_box_view(context *ctx)
        : vsh(GL_VERTEX_SHADER, 
              "#version 300 es",
              light_box_vsh)
        , fsh(GL_FRAGMENT_SHADER,
              "#version 300 es",
              lighting::fragment_source,
              light_box_fsh)
        , prog(&vsh, &fsh)
        , a_coord(&prog, "a_coord")
        , a_normal(&prog, "a_normal")
        , a_type(&prog, "a_type")
        , u_model_v(&prog, "u_model_v")
        , u_mvp_v(&prog, "u_mvp_v")
        , u_color_v(&prog, "u_color_v")
        , vbo(GL_ARRAY_BUFFER, 
              mesh, size_of_mesh)
        , light(std::make_unique<lighting>(ctx, &prog))
        , cam(ctx->get_part<camera>())
    {}

      template<typename _Iter>
    void light_box_view::draw(_Iter begin, _Iter end)
    {
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);



        prog.use();
        vbo.bind();

        auto offset = [](int n) -> void * {
            return reinterpret_cast<void *>(n * sizeof(GLfloat));
        };

        auto stride = sizeof(GLfloat) * 7;

        vertices = size_of_mesh / sizeof(float) / 3;

        a_coord.enable();
        a_type.enable();
        a_normal.enable();

        glVertexAttribPointer(a_coord, 3, GL_FLOAT,
                              GL_FALSE, stride,
                              offset(0));
        glVertexAttribPointer(a_type, 1, GL_FLOAT,
                              GL_FALSE, stride,
                              offset(3));
        glVertexAttribPointer(a_normal, 3, GL_FLOAT,
                              GL_FALSE, stride,
                              offset(4));

        std::vector<glm::mat4> models;
        std::vector<glm::mat4> mvps;
        std::vector<glm::vec3> colors;
        int count = 0;

        for (auto it = begin; it != end; it++)
        {
            auto box = *it;

            auto model = box->get_model();
            auto mvp = cam->make_mvp(model);
            auto color = box->get_light_color();

            models.push_back(model);
            mvps.push_back(mvp);
            colors.push_back(color);
            count++;
        }

        light->calculate();

        glUniformMatrix4fv(u_model_v, count, GL_FALSE, 
                           glm::value_ptr(models.front()));
        glUniformMatrix4fv(u_mvp_v, count, GL_FALSE, 
                           glm::value_ptr(mvps.front()));
        glUniform3fv(u_color_v, count, 
                     glm::value_ptr(colors.front()));

        glDrawArraysInstanced(GL_TRIANGLES, 0, vertices, count);

        a_coord.disable();
        a_type.disable();
        a_normal.disable();
    }

    void light_box_view::begin_drawing(bool stripped)
    {}

    void light_box_view::draw(const light_box *box)
    {}

    void light_box_view::end_drawing()
    {}

    template void light_box_view::draw
    <std::set<light_box *>::iterator>(
            std::set<light_box *>::iterator begin, 
            std::set<light_box *>::iterator end);
}
