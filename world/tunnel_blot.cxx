/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include <common/exception.hxx>

#include "tunnel_blot.hxx"

namespace world
{
    tunnel_blot::tunnel_blot(context *ctx)
        : context_part(ctx)
    {
        std::default_random_engine eng;
        std::uniform_real_distribution<float> dis(0.0, 1.0);

        auto genval = [&eng, &dis]() -> float {
            return dis(eng);
        };

        for (auto &blot : blots)
            std::generate(blot.begin(), blot.end(), genval);
    }

    const tunnel_blot::blot_set &tunnel_blot::get(int hash) const
    {
        return blots[hash % blot_count];
    }
}
