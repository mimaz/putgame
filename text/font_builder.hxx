/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __text_font_builder_hxx
#define __text_font_builder_hxx

#include "ascii_font.hxx"
#include "vector_character.hxx"

namespace text
{
    class ascii_font;

    class font_builder
    {
    public:
        font_builder(),
        font_builder(const ascii_font &font),
        ~font_builder();

        void bind_texture(int code);

    private:
        std::map<int, GLuint> texmap;
        GLuint *textures;
        int count;
    };
}

#endif
