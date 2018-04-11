/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __common_math_hxx
#define __common_math_hxx

constexpr auto PI = static_cast<float>(M_PI);

std::ostream &operator<<(std::ostream &os, const glm::vec4 &vec);

std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec);

std::ostream &operator<<(std::ostream &os, const glm::vec2 &vec);

namespace common
{
    glm::vec3 position(const glm::mat4 &mat);
}

#endif
