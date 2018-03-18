/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_tunnel_data_hxx
#define __world_tunnel_data_hxx

#include "context_part.hxx"

namespace world
{
    class tunnel_data : public context_part
    {
    public:
        static constexpr auto data_set_count = 32;
        static constexpr auto data_set_size = 16;

        using data_set = std::array<GLfloat, data_set_size>;


        tunnel_data(context *ctx);

        const data_set &get(int hash) const;

    private:
        std::array<data_set, data_set_count> data;
    };
}

#endif
