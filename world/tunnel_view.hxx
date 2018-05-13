/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_tunnel_view_hxx
#define __world_tunnel_view_hxx

#include <putgame/common>

#include "lighting.hxx"
#include "tunnel_mesh.hxx"
#include "tunnel_path.hxx"

namespace world
{
    class camera;

    class tunnel_view : public common::context::object
    {
    public:
        static constexpr auto max_count = 4;

        tunnel_view(common::context *ctx);

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
