/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __math_math_hxx
#define __math_math_hxx

namespace math
{
    constexpr float pi = static_cast<float>(M_PI);

    glm::vec3 coord3d(const glm::mat4 &mat);

    glm::vec3 direction3d(const glm::mat4 &mat);

    glm::vec3 top3d(const glm::mat4 &mat);

    float sqdist(glm::vec3 p, glm::vec3 q);

    float sqdist(const glm::mat4 &p, const glm::mat4 &q);

    float sqdist(glm::vec3 p, const glm::mat4 &q);

    float sqdist(const glm::mat4 &p, glm::vec3 q);
}

std::ostream &operator<<(std::ostream &os, const glm::vec4 &vec);

std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec);

std::ostream &operator<<(std::ostream &os, const glm::vec2 &vec);

#endif
