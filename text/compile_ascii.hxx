/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __text_compile_ascii_hxx
#define __text_compile_ascii_hxx

#include "vector_character.hxx"

namespace text
{
    void compile_ascii(const ascii_character &ascii,
                       int width,
                       int height,
                       float thickness,
                       std::vector<point> &points,
                       std::vector<segment> &segments);
}

#endif
