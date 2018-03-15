/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_trajak_hxx
#define __world_trajak_hxx

#include "context_part.hxx"
#include "shader.hxx"

namespace world
{
    class trajak : public context_part
    {
    public:
        trajak(context *ctx);
        ~trajak();

        void draw();

    private:
        GLuint program;
        GLuint a_coord;
        common::shader vshader;
        common::shader fshader;
    };
}

#endif
