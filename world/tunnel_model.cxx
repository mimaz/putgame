/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>
#include <putgame-res>

#include "tunnel_model.hxx"

#include "tunnel.hxx"
#include "tunnel_path.hxx"
#include "tunnel_data.hxx"
#include "camera.hxx"
#include "context.hxx"
#include "lighting.hxx"

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

    inline int frame_hash(const glm::mat4 &matrix, int index)
    {
        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++)
                index += static_cast<int>(matrix[y][x]);

        return std::hash<int>()(rand() + index);
    }
}

namespace world
{
    tunnel_model::tunnel_model(float width, int quality, 
                               bool stripped, tunnel *tun)
        : mesh(quality, width, stripped)
        , path(tun->get_context()->get_part<tunnel_path>())
        , data(tun->get_context()->get_part<tunnel_data>())
        , cam(tun->get_context()->get_part<camera>())
        , light(std::make_unique<world::lighting>(tun->get_context(), &prog))
        , path_segment_id(0)
        , vsh(GL_VERTEX_SHADER, tunnel_vsh)
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



        for (auto it = frames.begin() + 1; it != frames.end(); it++)
        {
            auto &fr0 = it[-1];
            auto &fr1 = it[0];

            auto rotate_model = [this](const frame &fr) -> glm::mat4 {
                auto idx = fr.get_index();

                auto angle = -PI / mesh.get_quality() * idx;
                auto axis = glm::vec3(0, 0, 1);

                auto rot = glm::rotate(glm::mat4(1), angle, axis);

                return fr.get_matrix() * rot;
            };


            auto model_0 = rotate_model(fr0);
            auto model_1 = rotate_model(fr1);

            u_model_0 = model_0;
            u_model_1 = model_1;

            u_mvp_0 = cam->make_mvp(model_0);
            u_mvp_1 = cam->make_mvp(model_1);


            auto random0 = data->get(fr0.get_hash()).data();
            auto random1 = data->get(fr1.get_hash()).data();

            glUniform1fv(u_random_0.get_handle(), 8, random0);
            glUniform1fv(u_random_1.get_handle(), 8, random1);


            glDrawElements(GL_TRIANGLES, mesh.get_index_count(), 
                           GL_UNSIGNED_BYTE, 0);
        }

        a_coord.disable();
        a_layer.disable();
        a_index.disable();
    }

    tunnel_model::frame::frame(const glm::mat4 &matrix, int index)
        : matrix(matrix)
        , index(index)
        , hash(frame_hash(matrix, index))
    {}

    float tunnel_model::frame::distance(const glm::vec3 &point) const
    {
        glm::vec3 coord = glm::vec3(get_matrix() * glm::vec4(0, 0, 0, 1));

        return glm::length(coord - point);
    }
}
