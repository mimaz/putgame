/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include <common/exception.hxx>

#include "tunnel_data.hxx"

namespace world
{
    tunnel_data::tunnel_data(context *ctx)
        : context_part(ctx)
    {
        for (auto &set : data)
            for (auto &v : set)
                v = static_cast<float>(rand()) / RAND_MAX;
    }

    const tunnel_data::data_set &tunnel_data::get(int hash) const
    {
        return data[hash % data_set_count];
    }
}
