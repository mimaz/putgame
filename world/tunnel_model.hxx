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
    class camera;
    class tunnel;
    class tunnel_path;

    class tunnel_model
    {
    public:
        class frame;

        tunnel_model(float width, int quality, bool stripped, tunnel *tun);

        ~tunnel_model();


        void gen_frame();

        void draw();

        const frame &get_last_frame() const { return frames.back(); }

    private:
        std::deque<frame> frames;
        tunnel_mesh mesh;

        tunnel_path *path;
        camera *cam;

        int path_segment_id;

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
        frame(const glm::mat4 &matrix, int index);

        frame(const frame &) = default;
        frame(frame &&) = default;

        const glm::mat4 &get_matrix() const { return matrix; }
        int get_index() const { return index; }

        float distance(const glm::vec3 &point) const;

    private:
        glm::mat4 matrix;
        int index;
    };
}

#endif
