/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_tunnel_path_hxx
#define __world_tunnel_path_hxx

#include "path_line.hxx"

namespace world
{
    class tunnel_path : public path_line
    {
    public:
        class frame;

        tunnel_path(path_line *pattern, float gap);

        void gen_frame();

    private:
        path_line *pattern;

        int pattern_id;
    };
}

#endif
