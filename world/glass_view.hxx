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
    class lighting;
    class glass_pane;
    class glass_piece;

    class glass_view
    {
    public:
        glass_view(context *ctx);

        void begin(bool specular);

        void bind_pane(bool specular);
        void bind_piece(bool specular);

        void draw(const glass_pane *pane, 
                  bool specular);

        void draw(const glass_piece *piece, 
                  bool specular);

        void end(bool specular);

    private:
        glutils::shader vsh;

        glutils::shader fsh_tr;
        glutils::program prog_tr;
        glutils::attribute a_coord_tr;
        glutils::uniform u_mvp_tr;
        glutils::uniform u_color_tr;

        glutils::shader fsh_sp;
        glutils::program prog_sp;
        glutils::attribute a_coord_sp;
        glutils::uniform u_model_sp;
        glutils::uniform u_mvp_sp;

        std::shared_ptr<lighting> light;

        camera *cam;
    };
}

#endif
