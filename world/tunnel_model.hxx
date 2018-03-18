/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_tunnel_model_hxx
#define __world_tunnel_model_hxx

#include <glutils/shader.hxx>
#include <glutils/program.hxx>
#include <glutils/uniform.hxx>
#include <glutils/attribute.hxx>

#include "tunnel_mesh.hxx"

namespace world
{
    class tunnel;

    class tunnel_model
    {
    public:
        class frame;

        tunnel_model(int quality, bool stripped, tunnel *tun);

        ~tunnel_model();

        void gen_frame();

        void draw();

    private:
        std::deque<frame> frames;
        tunnel_mesh mesh;

        tunnel *tun;
        int path_frame_id;

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program prog;
        glutils::attribute a_coord;
        glutils::attribute a_layer;
        glutils::uniform u_mvp_v;
    };

    class tunnel_model::frame
    {
    public:
        frame(int index, const glm::mat4 &matrix);

        frame(const frame &) = default;
        frame(frame &&) = default;

        int get_index() const { return index; }
        const glm::mat4 &get_matrix() const { return matrix; }
        float distance(const glm::vec3 &point) const;

    private:
        int index;
        glm::mat4 matrix;
    };
}

#endif
