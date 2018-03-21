/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_wall_obstacle_view_hxx
#define __world_wall_obstacle_view_hxx

#include <glutils/shader.hxx>
#include <glutils/program.hxx>
#include <glutils/attribute.hxx>
#include <glutils/uniform.hxx>
#include <glutils/buffer.hxx>

namespace world
{
    class context;
    class camera;
    class wall_obstacle;

    class wall_obstacle_view
    {
    public:
        wall_obstacle_view(context *ctx);
        ~wall_obstacle_view();

        void begin();
        void draw(const wall_obstacle *wall);
        void end();

    private:
        camera *cam;

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;
        glutils::attribute a_coord;
        glutils::attribute a_normal;
        glutils::attribute a_tex_coord;
        glutils::uniform u_model;
        glutils::uniform u_mvp;

        GLuint texhandle;
    };
}

#endif

