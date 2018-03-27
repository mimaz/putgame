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
        void set_font_size(const glm::vec2 &size);
        void set_font_size(float w, float h) { set_font_size({ w, h }); }

        const std::string &get_text() const { return text; }
        const glm::vec2 &get_font_size() const { return font_size; }
        int get_width() const { return width; }
        int get_height() const { return height; }

        float get_font_width() const { return get_font_size().x; }
        float get_font_height() const { return get_font_size().y; }

        GLuint get_texture_handle();

    private:
        void render();
        void measure();

        font_builder *builder;

        GLuint texhandle;

        std::string text;
        glm::vec2 font_size;

        int width;
        int height;

        bool dirty;
        bool resized;
    };
}

#endif
