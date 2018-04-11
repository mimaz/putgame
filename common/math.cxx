/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "math.hxx"

std::ostream &operator<<(std::ostream &os, const glm::vec4 &vec)
{
    return os << "[" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "]";
}

std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec)
{
    return os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
}

std::ostream &operator<<(std::ostream &os, const glm::vec2 &vec)
{
    return os << "[" << vec.x << ", " << vec.y << "]";
}

glm::vec3 common::position(const glm::mat4 &mat)
{
    return glm::vec3(mat * glm::vec4(0, 0, 0, 1));
}
