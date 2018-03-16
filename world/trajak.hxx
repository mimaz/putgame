/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_trajak_hxx
#define __world_trajak_hxx

#include "context_part.hxx"

#include "../glutils/shader.hxx"
#include "../glutils/program.hxx"
#include "../glutils/attribute.hxx"
#include "../glutils/uniform.hxx"

namespace world
{
    class trajak : public context_part
    {
    public:
        trajak(context *ctx);
        ~trajak();

        void draw();

    private:
        glutils::shader vshader;
        glutils::shader fshader;
        glutils::program program;
        glutils::attribute a_coord;
        glutils::attribute a_color;
        glutils::uniform u_matrix;
    };
}

#endif
