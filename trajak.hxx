/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_trajak_hxx
#define __world_trajak_hxx

#include "context_part.hxx"
#include "shader.hxx"
#include "program.hxx"

namespace world
{
    class trajak : public context_part
    {
    public:
        trajak(context *ctx);
        ~trajak();

        void draw();

    private:
        GLuint a_coord;
        glutils::shader vshader;
        glutils::shader fshader;
        glutils::program program;
    };
}

#endif
