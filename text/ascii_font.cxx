/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "ascii_font.hxx"

namespace text
{
    ascii_font::ascii_font(float thickness,
                           int width,
                           int height,
                           const char_list &characters)
        : thickness(thickness)
        , width(width)
        , height(height)
    {
        std::copy(characters.begin(), 
                  characters.end(),
                  std::back_inserter(vec));
    }

    int ascii_font::get_count() const
    {
        return static_cast<int>(vec.size());
    }

    const ascii_character *ascii_font::begin() const
    {
        return vec.data();
    }

    const ascii_character *ascii_font::end() const
    {
        return vec.data() + vec.size();
    }
}
