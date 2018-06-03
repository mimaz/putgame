/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/common>

#include "vector_character.hxx"

#include "compile_ascii.hxx"

namespace text
{
    vector_character::vector_character(const ascii_character &ascii,
                                       int ascii_width,
                                       int ascii_height,
                                       float thickness)
        : code(ascii.get_code())
        , thickness(thickness)
        , ratio(static_cast<float>(ascii_height) / ascii_width)
    {
        compile_ascii(ascii, ascii_width, ascii_height,
                      thickness, points, segments);
    }
}
