/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_glass_view_hxx
#define __world_glass_view_hxx

#include <glutils/shader.hxx>
#include <glutils/program.hxx>
#include <glutils/attribute.hxx>
#include <glutils/uniform.hxx>

namespace world
{
    class context;
    class camera;
    class glass_pane;
    class glass_piece;

    class glass_view
    {
    public:
        glass_view(context *ctx);

        void begin();

        void bind_pane();
        void bind_piece();

        void draw(const glass_pane *pane);
        void draw(const glass_piece *piece);

        void end();

    private:
        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program prog;
        glutils::attribute a_coord;
        glutils::uniform u_mvp;
        glutils::uniform u_color;

        camera *cam;
    };
}

#endif
