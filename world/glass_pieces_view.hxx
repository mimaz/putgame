/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __glass_pieces_view_hxx
#define __glass_pieces_view_hxx

#include <putgame/common-fwd>

#include "lighting.hxx"

namespace world
{
    class camera;
    class glass_pieces;

    class glass_pieces_view
    {
    public:
        glass_pieces_view(common::context *ctx);

        void begin();
        void draw(glass_pieces *pieces);
        void end();

    private:
        camera *cam;

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;
        glutils::uniform u_extra_v;
        glutils::uniform u_model_v;
        glutils::uniform u_view_proj;
        glutils::uniform u_specular_mode;
        glutils::uniform u_color;

        lighting light;
    };
}

#endif
