/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __text_caption_buffer_hxx
#define __text_caption_buffer_hxx

namespace text
{
    class caption_buffer
    {
    public:
        caption_buffer();
        caption_buffer(const std::string &text);

        caption_buffer(const caption_buffer &) = delete;
        caption_buffer(caption_buffer &&) = default;

        ~caption_buffer();

        void set_text(const std::string &text);

        void render();

        const std::string &get_text() const { return text; }

    private:
        GLuint texhandle;
        std::string text;
        bool dirty;
    };
}

#endif
