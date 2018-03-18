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
#include "tunnel_path.hxx"

namespace
{
    inline glm::vec3 get_position(const glm::mat4 &matrix)
    {
        return glm::vec3(matrix * glm::vec4(0, 0, 0, 1));
    }

    inline glm::vec3 get_direction(const glm::mat4 &matrix)
    {
        return glm::vec3(matrix * glm::vec4(0, 0, 1, 0));
    }
}

namespace world
{
    tunnel_model::tunnel_model(float width, int quality, 
                               bool stripped, tunnel *tun)
        : mesh(quality, width, stripped)
        , path(tun->get_context()->get_part<tunnel_path>())
        , cam(tun->get_context()->get_part<camera>())
        , path_segment_id(0)
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
        if (frames.empty())
        {
            frames.push_back(frame(glm::mat4(1), 0)); 
            return;
        }


        auto calc_target_coord = [this](void) -> glm::vec3 {
            auto mat = path->get_by_id(path_segment_id).get_matrix();

            return get_position(mat);
        };


        auto last_coord = get_position(get_last_frame().get_matrix());
        auto target_coord = calc_target_coord();


        auto gap = mesh.get_gap();


        while (glm::length(target_coord - last_coord) < gap)
        {
            path_segment_id++;
            target_coord = calc_target_coord();
        }



        auto last_direction = glm::normalize(
            get_direction(get_last_frame().get_matrix())
        );

        auto new_direction = glm::normalize(
            target_coord - last_coord
        );

        auto axis = glm::normalize(
            glm::cross(last_direction, new_direction)
        );

        auto angle = acosf(
            glm::dot(new_direction, last_direction)
        );

        
        auto index = get_last_frame().get_index() + 1;
        auto transform = get_last_frame().get_matrix();

        transform = glm::translate(transform, glm::vec3(0, 0, gap));
        transform = glm::rotate(transform, angle, axis);



        frames.emplace_back(transform, index);
    }

    void tunnel_model::draw()
    {
        if (frames.empty())
            return;


        glEnable(GL_CULL_FACE);

        prog.use();

        a_coord.enable();
        a_layer.enable();



        glBindBuffer(GL_ARRAY_BUFFER, 0);

        for (auto it = frames.begin() + 1; it != frames.end(); it++)
        {
            auto fr1 = it[-1];
            auto fr2 = it[0];

            auto make_mvp = [this](const frame &fr) -> glm::mat4 {
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

    tunnel_model::frame::frame(const glm::mat4 &matrix, int index)
        : matrix(matrix)
        , index(index)
    {}

    float tunnel_model::frame::distance(const glm::vec3 &point) const
    {
        glm::vec3 coord = glm::vec3(get_matrix() * glm::vec4(0, 0, 0, 1));

        return glm::length(coord - point);
    }
}
