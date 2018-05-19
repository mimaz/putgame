/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_tunnel_path_hxx
#define __world_tunnel_path_hxx

#include <putgame/common>

#include "path_line.hxx"

namespace world
{
    class way_path;

    class tunnel_path : public path_line
    {
    public:
        class frame;

        tunnel_path(common::context *ctx, float gap);

        void reset() override;
        void update();

    private:
        void generate();

        int way_frame_id;
        int way_frame_step;
    };
}

#endif
