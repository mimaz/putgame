/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>
#include <putgame-res>

#include <glutils/shader.hxx>
#include <glutils/program.hxx>
#include <glutils/uniform.hxx>
#include <glutils/attribute.hxx>

#include "tunnel.hxx"

#include "context_part.hxx"
#include "context.hxx"
#include "tunnel_mesh.hxx"
#include "camera.hxx"

namespace world
{
    class drawer : public context_part
    {
    public:
        using frame = world::tunnel::frame;

        drawer(context *ctx)
            : context_part(ctx)
            , mesh(12, 2, true)
            , vsh(GL_VERTEX_SHADER, tunnel_vsh)
            , fsh(GL_FRAGMENT_SHADER, tunnel_fsh)
            , prog(&vsh, &fsh)
            , a_coord(&prog, "a_coord")
            , a_layer(&prog, "a_layer")
            , u_mvp_v(&prog, "u_mvp_v")
        {}

        void draw_begin()
        {
            glEnable(GL_CULL_FACE);

            prog.use();

            a_coord.enable();
            a_layer.enable();
        }

        void draw_frames(const frame &fr1, const frame &fr2)
        {
            auto cam = get_context()->get_part<world::camera>();


            glBindBuffer(GL_ARRAY_BUFFER, 0);


            auto make_mvp = [cam](const frame &fr) -> glm::mat4 {
                auto idx = fr.get_index();
                auto axis = glm::vec3(0, 0, 1);
                auto rot = glm::rotate(glm::mat4(1), -PI / 12 * idx, axis);

                return cam->get_mvp(fr.get_model() * rot);
            };


            glm::mat4 mvp_v[2] = {
                make_mvp(fr1),
                make_mvp(fr2),
            };

            glUniformMatrix4fv(u_mvp_v.get_handle(), 2, GL_FALSE, 
                               glm::value_ptr(mvp_v[0]));

            glVertexAttribPointer(a_coord, 3, GL_FLOAT,
                                  GL_FALSE, sizeof(GLfloat) * 4,
                                  mesh.get_vertex_ptr());
            glVertexAttribPointer(a_layer, 1, GL_FLOAT,
                                  GL_FALSE, sizeof(GLfloat) * 4,
                                  mesh.get_vertex_ptr() + 3);


            glDrawElements(GL_TRIANGLES, mesh.get_index_count(), 
                           GL_UNSIGNED_SHORT, mesh.get_index_ptr());
        }

        void draw_end()
        {
            a_coord.disable();
            a_layer.disable();
        }

        tunnel_mesh mesh;

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program prog;
        glutils::attribute a_coord;
        glutils::attribute a_layer;
        glutils::uniform u_mvp_v;
    };

    tunnel::tunnel(context *ctx)
        : context_part(ctx)
        , camera_index(0)
    {}

    void tunnel::append(float distance, float angle, const glm::vec3 &axis)
    {
        auto transform = glm::translate(glm::mat4(1), glm::vec3(0, 0, 1));

        transform = glm::rotate(transform, angle, axis);

        append(transform);
    }

    void tunnel::append(const glm::mat4 &transform)
    {
        if (list.empty())
        {
            auto fr = frame(0, transform);

            list.push_back(fr);
        }
        else
        {
            auto index = list.back().get_index() + 1;
            auto model = list.back().get_model() * transform;

            auto fr = frame(index, model);

            list.push_back(fr);
        }
    }

    void tunnel::draw()
    {
        if (list.size() > 1)
        {
            auto dr = get_context()->get_part<drawer>();

            dr->draw_begin();

            for (auto it = list.begin() + 1; it != list.end(); it++)
                dr->draw_frames(it[-1], it[0]);

            dr->draw_end();
        }
    }

    void tunnel::update_camera_index()
    {
        // TODO
    }

    tunnel::frame::frame(int index, const glm::mat4 &model)
        : index(index)
        , model(model)
    {}

    float tunnel::frame::distance(const glm::vec3 &point) const
    {
        glm::vec3 coord = glm::vec3(get_model() * glm::vec4(0, 0, 0, 1));

        return glm::length(coord - point);
    }
}
