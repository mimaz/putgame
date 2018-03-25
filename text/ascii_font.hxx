/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __text_ascii_font_hxx
#define __text_ascii_font_hxx

#include "ascii_character.hxx"

namespace text
{
    class ascii_font
    {
    public:
        using char_list = std::initializer_list<ascii_character>;
        using char_vec = std::vector<ascii_character>;

        ascii_font(float thickness,
                   int width,
                   int height,
                   const char_list &characters);

        float get_thickness() const { return thickness; }
        int get_width() const { return width; }
        int get_height() const { return height; }
        int get_count() const;

        const ascii_character *begin() const;
        const ascii_character *end() const;

    private:
        char_vec vec;
        float thickness;
        int width;
        int height;
    };
}

#endif
