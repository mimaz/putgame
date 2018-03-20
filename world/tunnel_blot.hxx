/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_tunnel_blot_hxx
#define __world_tunnel_blot_hxx

#include "context_part.hxx"

namespace world
{
    class tunnel_blot : public context_part
    {
    public:
        static constexpr auto blot_count = 16;
        static constexpr auto blot_size = 8;

        using blot_set = std::array<float, blot_size>;


        tunnel_blot(context *ctx);

        const blot_set &get(int hash) const;

    private:
        std::array<blot_set, blot_count> blots;
    };
}

#endif
