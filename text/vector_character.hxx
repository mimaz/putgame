/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __text_vector_character_hxx
#define __text_vector_character_hxx

#include "ascii_character.hxx"

namespace text
{
    using point = glm::vec2;
    using segment = std::pair<point, point>;

    class vector_character
    {
    public:
        vector_character(const ascii_character &ascii,
                         int ascii_width,
                         int ascii_height,
                         float thickness);

        vector_character(const vector_character &) = default;
        vector_character(vector_character &&) = default;

        const std::vector<point> get_points() const { return points; }
        const std::vector<segment> get_segments() const { return segments; }
        int get_code() const { return code; }
        float get_thickness() const { return thickness; }
        float get_ratio() const { return ratio; }

    private:
        std::vector<point> points;
        std::vector<segment> segments;
        int code;
        float thickness;
        float ratio;
    };
}

#endif
