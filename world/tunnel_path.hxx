/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_tunnel_path_hxx
#define __world_tunnel_path_hxx

#include "path_line.hxx"

namespace world
{
    class way_path;

    class tunnel_path : public path_line
    {
    public:
        class frame;

        tunnel_path(way_path *way, float gap);

        void gen_frame_back();

    private:
        way_path *way;

        int way_back_id;
    };
}

#endif
