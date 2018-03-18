/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_tunnel_view_hxx
#define __world_tunnel_view_hxx

#include <glutils/shader.hxx>
#include <glutils/program.hxx>
#include <glutils/uniform.hxx>
#include <glutils/attribute.hxx>
#include <glutils/buffer.hxx>

#include "tunnel_mesh.hxx"

namespace world
{
    class camera;
    class lighting;
    class tunnel;
    class tunnel_path;
    class tunnel_data;

    class tunnel_view
    {
    public:
        class frame;

        tunnel_view(float width, int quality, bool stripped, tunnel *tun);

        ~tunnel_view();


        void gen_frame();

        void draw();

        const frame &get_last_frame() const { return frames.back(); }

    private:
        std::deque<frame> frames;
        tunnel_mesh mesh;

        tunnel_path *path;
        tunnel_data *data;
        camera *cam;
        std::unique_ptr<lighting> light;

        int path_segment_id;

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program prog;
        glutils::attribute a_coord;
        glutils::attribute a_layer;
        glutils::attribute a_index;
        glutils::uniform u_model_0;
        glutils::uniform u_model_1;
        glutils::uniform u_mvp_0;
        glutils::uniform u_mvp_1;
        glutils::uniform u_random_0;
        glutils::uniform u_random_1;
        glutils::buffer vbo;
        glutils::buffer ibo;
    };

    class tunnel_view::frame
    {
    public:
        frame(const glm::mat4 &matrix, int index);

        frame(const frame &) = default;
        frame(frame &&) = default;

        const glm::mat4 &get_matrix() const { return matrix; }
        int get_index() const { return index; }
        int get_hash() const { return hash; }

        float distance(const glm::vec3 &point) const;

    private:
        glm::mat4 matrix;
        int index;
        int hash;
    };
}

#endif
