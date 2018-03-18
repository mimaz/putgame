/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_tunnel_hxx
#define __world_tunnel_hxx

#include "context_part.hxx"

namespace world
{
    class tunnel_model;

    class tunnel : public context_part
    {
    public:
        class frame;

        tunnel(context *ctx);

        void draw();

    private:
        std::shared_ptr<tunnel_model> model;
    };
}

#endif
