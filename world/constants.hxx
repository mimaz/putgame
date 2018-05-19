/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_constants_hxx
#define __world_constants_hxx

namespace world
{
    constexpr auto tunnel_radius = 1;
    constexpr auto tunnel_width = tunnel_radius * 2;
    constexpr auto tunnel_quality = 20;
    constexpr auto light_box_size = 0.15f;
    constexpr auto way_frame_gap = 1.0f / 16;

    constexpr auto tunnel_square_area = glm::vec2(tunnel_width);
}

#endif
