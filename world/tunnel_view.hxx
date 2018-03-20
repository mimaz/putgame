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

namespace world
{
    class camera;
    class lighting;
    class tunnel;
    class pathway;
    class tunnel_blot;

    class tunnel_view
    {
    public:
        tunnel_view(float width, int quality, bool stripped, tunnel *tun);

        void draw();

    private:
        tunnel_mesh mesh;
        tunnel_path path;

        tunnel_blot *blot;
        camera *cam;
        std::shared_ptr<lighting> light;

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

}

#endif
