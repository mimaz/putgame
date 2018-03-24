/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __common_color_hxx
#define __common_color_hxx

namespace common
{
    inline glm::vec3 white(float v)
    {
        return glm::vec3(v, v, v);
    }

    inline glm::vec3 red(float b = 1, float d = 0)
    {
        return glm::vec3(b, d, d);
    }

    inline glm::vec3 green(float b = 1, float d = 0)
    {
        return glm::vec3(d, b, d);
    }

    inline glm::vec3 blue(float b = 1, float d = 0)
    {
        return glm::vec3(d, d, b);
    }

    inline glm::vec3 yellow(float b = 1, float d = 0)
    {
        return glm::vec3(b, b, d);
    }

    inline glm::vec3 purple(float b = 1, float d = 0)
    {
        return glm::vec3(b, d, b);
    }

    inline glm::vec3 black() 
    {
        return glm::vec3(0.0f, 0.0f, 0.0f);
    }
}

#endif
