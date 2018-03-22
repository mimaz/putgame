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
#include "tunnel_path.hxx"
#include "lighting.hxx"

namespace world
{
    class camera;
    class tunnel;

    class tunnel_view
    {
    public:
        static constexpr auto max_count = 4;

        tunnel_view(float width, int quality, tunnel *tun);

        void draw();

        tunnel_path *get_path() { return &path; }

    private:
        void begin_drawing();
        void draw(const path_point &pt);
        void end_drawing();
        void draw_segments();

        tunnel_mesh mesh;
        tunnel_path path;

        lighting light;

        camera *cam;

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program prog;
        glutils::attribute a_coord;
        glutils::uniform u_model_v;
        glutils::uniform u_mvp_v;
        glutils::uniform u_hash_v;
        glutils::buffer vbo;
        glutils::buffer ibo;

        std::array<glm::mat4, max_count> models;
        std::array<glm::mat4, max_count> mvps;
        std::array<GLint, max_count> hashes;

        int count;
    };

}

#endif
