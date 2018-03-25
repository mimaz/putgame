/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __text_font_builder_hxx
#define __text_font_builder_hxx

#include "vector_character.hxx"

namespace text
{
    class font_builder
    {
    public:
        font_builder(int count = 128),
        ~font_builder();

        void render(const vector_character *begin, 
                    const vector_character *end);

        void render(const ascii_character *begin,
                    const ascii_character *end,
                    int ascii_width,
                    int ascii_height,
                    float thickness);

        void bind_texture(int code);

    private:
        GLuint *textures;
        int count;
    };
}

#endif
