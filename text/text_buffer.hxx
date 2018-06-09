/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __text_text_buffer_hxx
#define __text_text_buffer_hxx

#include <putgame/common>

namespace text
{
    class font_builder;

    class text_buffer : public common::context::object
    {
    public:
        PUTGAME_OBJECT

        text_buffer(common::context *ctx,
                    font_builder *builder);
        text_buffer(common::context *ctx, 
                    font_builder *builder,
                    const std::string &text);

        text_buffer(const text_buffer &) = delete;
        text_buffer(text_buffer &&) = default;

        ~text_buffer();


        void set_text(const std::string &text);
        void set_size(int width, int height);
        void set_font_size(float size);

        const std::string &get_text() const { return text; }
        float get_font_size() const { return font_size; }
        int get_width() const { return width; }
        int get_height() const { return height; }
        int get_text_width() const { return text_width; }
        int get_text_height() const { return text_height; }

        GLuint get_texture_handle();

    private:
        void render();

        font_builder *builder;
        GLuint texhandle;

        std::string text;
        float font_size;
        int width;
        int height;

        int text_width;
        int text_height;

        bool dirty;
        bool resized;
    };
}

#endif
