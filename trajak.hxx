/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_trajak_hxx
#define __world_trajak_hxx

#include "context_part.hxx"
#include "shader.hxx"
#include "program.hxx"
#include "attribute.hxx"
#include "uniform.hxx"

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
