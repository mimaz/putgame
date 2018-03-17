/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "rgb_color.hxx"

namespace common
{
    const rgb_color rgb_color::red(1, 0, 0);
    const rgb_color rgb_color::green(0, 1, 0);
    const rgb_color rgb_color::blue(0, 0, 1);
    const rgb_color rgb_color::white(1, 1, 1);
    const rgb_color rgb_color::black(0, 0, 0);

    rgb_color::rgb_color(float rgb)
        : rgb_color(rgb, rgb, rgb) {}

    rgb_color::rgb_color(float r, float g, float b)
        : rgb_color(glm::vec3(r, g, b)) {}

    rgb_color::rgb_color(const glm::vec3 &vec)
        : vec(vec) {}
}
