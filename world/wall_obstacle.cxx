/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "wall_obstacle.hxx"

namespace 
{
    constexpr auto scale_factor = 0.1f;
}

namespace world
{
    wall_obstacle::wall_obstacle(context *ctx, glm::vec2 siz)
        : abstract_obstacle(ctx)
        , size(siz)
    {
        scale(glm::vec3(siz * scale_factor, 1.0f));

        register_self(this);
    }
}
