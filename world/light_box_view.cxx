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

namespace 
{
    common::rgb_color to_rgb(world::light_box::color col)
    {
        const auto bright = 1.0f;
        const auto dim = 0.8f;

        switch (col)
        {
            case world::light_box::red:
                return common::rgb_color(bright, dim, dim);

            case world::light_box::green:
                return common::rgb_color(dim, bright, dim);

            case world::light_box::blue:
                return common::rgb_color(dim, dim, bright);
        }

        throw common::make_invalid_argument(col);
    }
}

namespace world
{
    light_box_view::light_box_view(context *ctx)
        : vsh(GL_VERTEX_SHADER, light_box_vsh)
        , fsh(GL_FRAGMENT_SHADER,
              lighting::fragment_source,
              light_box_fsh)
        , prog(&vsh, &fsh)
        , a_coord(&prog, "a_coord")
        , a_normal(&prog, "a_normal")
        , a_type(&prog, "a_type")
        , u_model(&prog, "u_model")
        , u_mvp(&prog, "u_mvp")
        , u_color(&prog, "u_color")
        , vbo(GL_ARRAY_BUFFER, 
              mesh, size_of_mesh)
        , light(std::make_unique<lighting>(ctx, &prog))
        , cam(ctx->get_part<camera>())
    {}

    void light_box_view::begin_drawing(bool stripped)
    {
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);

        prog.use();

        a_coord.enable();
        a_normal.enable();
        a_type.enable();


        light->calculate();


        auto offset = [stripped](int n) -> void * {
            return reinterpret_cast<void *>(n * sizeof(GLfloat));
        };

        auto stride = sizeof(GLfloat) * 7;

        vertices = size_of_mesh / sizeof(float) / 3;

        if (stripped)
        {
            // TODO it's not working
            stride *= 2;
            vertices /= 4;
        }


        vbo.bind();


        glVertexAttribPointer(a_coord, 3, GL_FLOAT,
                              GL_FALSE, stride,
                              offset(0));
        glVertexAttribPointer(a_type, 1, GL_FLOAT,
                              GL_FALSE, stride,
                              offset(3));
        glVertexAttribPointer(a_normal, 3, GL_FLOAT,
                              GL_FALSE, stride,
                              offset(4));
    }

    void light_box_view::draw(const light_box *box)
    {
        auto model = box->get_model();


        model = glm::rotate(model, box->get_angle(), 
                            glm::vec3(0, 0, 1));
        model = glm::rotate(model, box->get_angle() / 2, 
                            glm::vec3(0, 1, 0));
        model = glm::rotate(model, box->get_angle() / 3, 
                            glm::vec3(1, 0, 0));


        u_model = model;
        u_mvp = cam->make_mvp(model);
        u_color = to_rgb(box->get_color());


        glDrawArrays(GL_TRIANGLES, 0, vertices);
    }

    void light_box_view::end_drawing()
    {
        a_coord.disable();
        a_type.disable();
        a_normal.disable();
    }
}
