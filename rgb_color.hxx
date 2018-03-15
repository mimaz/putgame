/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __common_rgb_color_hxx
#define __common_rgb_color_hxx

namespace common
{
    class rgb_color
    {
    public:
        static const rgb_color red;
        static const rgb_color green;
        static const rgb_color blue;
        static const rgb_color white;
        static const rgb_color black;

        rgb_color(float rgb);
        rgb_color(float r, float g, float b);
        rgb_color(const glm::vec3 &rgb);

        rgb_color(const rgb_color &) = default;
        rgb_color(rgb_color &&) = default;

        float &operator[](int idx) { return vec[idx]; }
        float operator[](int idx) const { return vec[idx]; }

        operator glm::vec3() const { return vec; }

    private:
        glm::vec3 vec;
    };
}

#endif
