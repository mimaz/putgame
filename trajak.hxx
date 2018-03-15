/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_trajak_hxx
#define __world_trajak_hxx

#include "context_part.hxx"

namespace world
{
    class trajak : public context_part
    {
    public:
        trajak(context *ctx);
        ~trajak();

        void draw();

    private:
        GLuint vshader;
        GLuint fshader;
        GLuint program;
        GLuint a_coord;
    };
}

#endif
