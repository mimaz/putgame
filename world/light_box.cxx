/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>
#include <putgame-res>

#include <glutils/program.hxx>
#include <glutils/shader.hxx>
#include <glutils/attribute.hxx>
#include <glutils/uniform.hxx>

#include <common/rgb_color.hxx>
#include <common/exception.hxx>

#include "light_box.hxx"

#include "context_part.hxx"
#include "context.hxx"
#include "camera.hxx"
#include "lighting.hxx"


constexpr auto size = 1.0f;


namespace 
{
    common::rgb_color to_rgb(world::light_box::color col)
    {
        const auto bright = 1.0f;
        const auto dim = 0.6f;

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

    class drawer : public world::context_part
    {
    public:
        drawer(world::context *ctx) 
            : context_part(ctx)
            , vsh(GL_VERTEX_SHADER, light_box_vsh)
            , fsh(GL_FRAGMENT_SHADER, 
                  world::lighting::fragment_source,
                  light_box_fsh)
            , prog(&vsh, &fsh)
            , a_coord(&prog, "a_coord")
            , a_type(&prog, "a_type")
            , a_normal(&prog, "a_normal")
            , u_mvp(&prog, "u_mvp")
            , u_model(&prog, "u_model")
            , u_color(&prog, "u_color")
            , light(std::make_unique<world::lighting>(ctx, &prog))
        {}

        void draw(world::light_box *box)
        {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);


            prog.use();

            a_coord.enable();
            a_type.enable();
            a_normal.enable();


            light->calculate();


            auto model = box->get_model();

            model = glm::rotate(model, box->get_angle(), 
                                glm::vec3(0, 0, 1));
            model = glm::rotate(model, box->get_angle() / 2, 
                                glm::vec3(0, 1, 0));
            model = glm::rotate(model, box->get_angle() / 3, 
                                glm::vec3(1, 0, 0));

            u_mvp = get_context()->get_part<world::camera>()->get_mvp(model);
            u_model = model;
            u_color = to_rgb(box->get_color());

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glVertexAttribPointer(a_coord, 3, GL_FLOAT,
                                  GL_FALSE, sizeof(GLfloat) * 7,
                                  light_box_mesh);
            glVertexAttribPointer(a_type, 1, GL_FLOAT,
                                  GL_FALSE, sizeof(GLfloat) * 7,
                                  light_box_mesh + 3);
            glVertexAttribPointer(a_normal, 3, GL_FLOAT,
                                  GL_FALSE, sizeof(GLfloat) * 7,
                                  light_box_mesh + 4);



            glDrawArrays(GL_TRIANGLES, 0, light_box_mesh_size / 3);


            a_coord.disable();
            a_type.disable();
            a_normal.disable();
        }

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program prog;
        glutils::attribute a_coord;
        glutils::attribute a_type;
        glutils::attribute a_normal;
        glutils::uniform u_mvp;
        glutils::uniform u_model;
        glutils::uniform u_color;

        std::unique_ptr<world::lighting> light;
    };
}

namespace world
{
    light_box::light_box(context *ctx, color col)
        : visible_object(ctx)
        , col(col)
        , speed(0.05)
        , angle(0)
        , blur(0)
    {}

    void light_box::set_color(color c)
    {
        col = c;
    }

    void light_box::set_speed(float spd)
    {
        speed = spd;
    }

    void light_box::draw()
    {
        angle += get_speed();

        get_context()->get_part<drawer>()->draw(this);
    }
}
