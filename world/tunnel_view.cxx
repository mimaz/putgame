/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>
#include <putgame-res>

#include "tunnel_view.hxx"

#include "tunnel.hxx"
#include "way_path.hxx"
#include "tunnel_blot.hxx"
#include "camera.hxx"
#include "context.hxx"
#include "lighting.hxx"

namespace
{
    std::string vsh_header(int blot_size)
    {
        return "const int blot_size = " + std::to_string(blot_size) + ";\n";
    }

    int frame_hash(const world::path_point &pt)
    {
        return pt.get_index();
    }
}

namespace world
{
    tunnel_view::tunnel_view(float width, int quality, 
                             bool stripped, tunnel *tun)
        : mesh(quality, width, stripped)
        , path(tun->get_context()->get_part<way_path>(), mesh.get_gap())
        , blot(tun->get_context()->get_part<tunnel_blot>())
        , cam(tun->get_context()->get_part<camera>())
        , light(std::make_shared<world::lighting>(tun->get_context(), &prog))
        , vsh(GL_VERTEX_SHADER, 
              vsh_header(tunnel_blot::blot_size),
              tunnel_vsh)
        , fsh(GL_FRAGMENT_SHADER, 
              world::lighting::fragment_source,
              tunnel_fsh)
        , prog(&vsh, &fsh)
        , a_coord(&prog, "a_coord")
        , a_layer(&prog, "a_layer")
        , a_index(&prog, "a_index")
        , u_model_0(&prog, "u_model_0")
        , u_model_1(&prog, "u_model_1")
        , u_mvp_0(&prog, "u_mvp_0")
        , u_mvp_1(&prog, "u_mvp_1")
        , u_random_0(&prog, "u_random_0")
        , u_random_1(&prog, "u_random_1")
        , vbo(GL_ARRAY_BUFFER, mesh.get_vertex_ptr(), 
              mesh.get_vertex_data_size())
        , ibo(GL_ELEMENT_ARRAY_BUFFER, mesh.get_index_ptr(),
              mesh.get_index_count())
    {}

    void tunnel_view::draw()
    {
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);


        auto &points = path.get_points();

        if (points.empty())
            return;

        prog.use();

        a_coord.enable();
        a_layer.enable();
        a_index.enable();


        light->calculate();



        vbo.bind();
        ibo.bind();


        auto offset = [](GLuint n) -> void * {
            return reinterpret_cast<void *>(n * sizeof(GLfloat));
        };

        auto stride = sizeof(GLfloat) * 5;


        glVertexAttribPointer(a_coord, 3, GL_FLOAT,
                              GL_FALSE, stride,
                              offset(0));

        glVertexAttribPointer(a_layer, 1, GL_FLOAT,
                              GL_FALSE, stride,
                              offset(3));

        glVertexAttribPointer(a_index, 1, GL_FLOAT,
                              GL_FALSE, stride,
                              offset(4));



        for (auto it = points.begin() + 1; it != points.end(); it++)
        {
            auto &pt0 = it[-1];
            auto &pt1 = it[0];

            auto rotate_model = [this](const path_point &pt) -> glm::mat4 {
                auto idx = pt.get_index();

                auto angle = -PI / mesh.get_quality() * idx;
                auto axis = glm::vec3(0, 0, 1);

                auto rot = glm::rotate(glm::mat4(1), angle, axis);

                return pt.get_matrix() * rot;
            };


            auto model_0 = rotate_model(pt0);
            auto model_1 = rotate_model(pt1);


            u_model_0 = model_0;
            u_model_1 = model_1;

            u_mvp_0 = cam->make_mvp(model_0);
            u_mvp_1 = cam->make_mvp(model_1);


            auto random0 = blot->get(frame_hash(pt0)).data();
            auto random1 = blot->get(frame_hash(pt1)).data();

            auto blot_size = tunnel_blot::blot_size;

            glUniform1fv(u_random_0.get_handle(), blot_size, random0);
            glUniform1fv(u_random_1.get_handle(), blot_size, random1);


            glDrawElements(GL_TRIANGLES, mesh.get_index_count(), 
                           GL_UNSIGNED_BYTE, 0);
        }

        a_coord.disable();
        a_layer.disable();
        a_index.disable();
    }
}
