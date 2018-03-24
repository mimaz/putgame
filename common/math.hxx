/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __common_math_hxx
#define __common_math_hxx

constexpr auto PI = static_cast<float>(M_PI);

inline std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec)
{
    return os << vec.x << ", " << vec.y << ", " << vec.z;
}

#endif
