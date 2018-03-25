/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "caption_buffer.hxx"

namespace text
{
    caption_buffer::caption_buffer()
        : text("dupa")
        , dirty(true)
    {
        glGenTextures(1, &texhandle);
    }

    caption_buffer::caption_buffer(const std::string &text)
        : caption_buffer()
    {
        set_text(text);
    }

    caption_buffer::~caption_buffer()
    {
        glDeleteTextures(1, &texhandle);
    }

    void caption_buffer::set_text(const std::string &txt)
    {
        text = txt;
    }

    void caption_buffer::render()
    {
        
    }
}
