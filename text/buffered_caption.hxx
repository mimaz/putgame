/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __text_buffered_caption_hxx
#define __text_buffered_caption_hxx

#include <putgame/common>

namespace text
{
    class font_builder;

    class buffered_caption : public common::context::object
    {
    public:
        buffered_caption(common::context *ctx,
                       font_builder *builder);
        buffered_caption(common::context *ctx, 
                       font_builder *builder,
                       const std::string &text);

        buffered_caption(const buffered_caption &) = delete;
        buffered_caption(buffered_caption &&) = default;

        ~buffered_caption();


        void set_text(const std::string &text);
        void set_color(const glm::vec4 &color);
        void set_text_color(const glm::vec4 &color);
        void set_font_size(const glm::vec2 &size);
        void set_font_size(float w, float h) { set_font_size({ w, h }); }
        void set_width(int width);
        void set_height(int height);

        const std::string &get_text() const { return text; }
        const glm::vec4 &get_color() const { return color; }
        const glm::vec4 &get_text_color() const { return text_color; }
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
        glm::vec4 color;
        glm::vec4 text_color;
        glm::vec2 font_size;

        int width;
        int height;

        bool dirty;
        bool resized;
    };
}

#endif
