/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */


#include "math.hxx"

namespace math
{
    glm::vec3 coord3d(const glm::mat4 &mat)
    {
        return glm::vec3(mat * glm::vec4(0, 0, 0, 1));
    }

    glm::vec3 direction3d(const glm::mat4 &mat)
    {
        return glm::vec3(mat * glm::vec4(0, 0, 1, 0));
    }

    glm::vec3 top3d(const glm::mat4 &mat)
    {
        return glm::vec3(mat * glm::vec4(0, 1, 0, 0));
    }

    float sqdist(glm::vec3 p, glm::vec3 q)
    {
        auto d = p - q;

        d *= d;

        return d.x + d.y + d.z;
    }

    float sqdist(const glm::mat4 &p, const glm::mat4 &q)
    {
        return sqdist(coord3d(p), coord3d(q));
    }

    float sqdist(glm::vec3 p, const glm::mat4 &q)
    {
        return sqdist(p, coord3d(q));
    }

    float sqdist(const glm::mat4 &p, glm::vec3 q)
    {
        return sqdist(coord3d(p), q);
    }
}

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
