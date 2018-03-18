/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>
#include <putgame-res>

#include "tunnel_model.hxx"

#include "tunnel.hxx"
#include "camera.hxx"
#include "context.hxx"
#include "path.hxx"

namespace world
{
    tunnel_model::tunnel_model(int quality, bool stripped, tunnel *tun)
        : mesh(quality, tunnel::width, stripped)
        , tun(tun)
        , path_frame_id(0)
        , vsh(GL_VERTEX_SHADER, tunnel_vsh)
        , fsh(GL_FRAGMENT_SHADER, tunnel_fsh)
        , prog(&vsh, &fsh)
        , a_coord(&prog, "a_coord")
        , a_layer(&prog, "a_layer")
        , u_mvp_v(&prog, "u_mvp_v")
    {
        for (int i = 0; i < 10; i++)
            gen_frame();
    }

    tunnel_model::~tunnel_model()
    {}

    void tunnel_model::gen_frame()
    {
        if (list.empty())
        {
            list.push_back(frame(0, glm::mat4(1))); 
            return;
        }



        auto pt = tun->get_context()->get_part<path>();


        auto last = [this]() -> const frame & {
            return list.back();
        };

        auto calc_coord = [](const glm::mat4 &matrix) -> glm::vec3 {
            return glm::vec3(matrix * glm::vec4(0, 0, 0, 1));
        };

        auto calc_direction = [](const glm::mat4 &matrix) -> glm::vec3 {
            return glm::vec3(matrix * glm::vec4(0, 0, 1, 0));
        };

        auto calc_last_coord = [this, last, calc_coord](void) -> glm::vec3 {
            auto mat = last().get_matrix();

            return calc_coord(mat);
        };

        auto calc_path_coord = [this, pt, calc_coord](void) -> glm::vec3 {
            auto mat = pt->get_by_id(path_frame_id).get_matrix();

            return calc_coord(mat);
        };


        auto last_coord = calc_last_coord();
        auto path_coord = calc_path_coord();


        auto get_dist = [&path_coord, &last_coord]() -> float {
            return glm::length(path_coord - last_coord);
        };


        while (get_dist() < 1)
        {
            path_frame_id++;
            path_coord = calc_path_coord();
        }

        auto index = last().get_index() + 1;
        auto transform = pt->get_by_id(path_frame_id).get_matrix();

        list.emplace_back(index, transform);
    }

    void tunnel_model::draw()
    {
        if (list.empty())
            return;


        glEnable(GL_CULL_FACE);

        prog.use();

        a_coord.enable();
        a_layer.enable();


        auto cam = tun->get_context()->get_part<world::camera>();

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        for (auto it = list.begin() + 1; it != list.end(); it++)
        {
            auto fr1 = it[-1];
            auto fr2 = it[0];

            auto make_mvp = [cam](const frame &fr) -> glm::mat4 {
                auto idx = fr.get_index();
                auto axis = glm::vec3(0, 0, 1);
                auto rot = glm::rotate(glm::mat4(1), -PI / 12 * idx, axis);

                return cam->get_mvp(fr.get_matrix() * rot);
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

        a_coord.disable();
        a_layer.disable();
    }

    tunnel_model::frame::frame(int index, const glm::mat4 &matrix)
        : index(index)
        , matrix(matrix)
    {}

    float tunnel_model::frame::distance(const glm::vec3 &point) const
    {
        glm::vec3 coord = glm::vec3(get_matrix() * glm::vec4(0, 0, 0, 1));

        return glm::length(coord - point);
    }
}
