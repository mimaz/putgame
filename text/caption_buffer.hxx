/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __text_caption_buffer_hxx
#define __text_caption_buffer_hxx

#include <putgame/common>

namespace text
{
    class font_builder;

    class caption_buffer : public common::context::object
    {
    public:
        caption_buffer(common::context *ctx,
                       font_builder *builder);
        caption_buffer(common::context *ctx, 
                       font_builder *builder,
                       const std::string &text);

        caption_buffer(const caption_buffer &) = delete;
        caption_buffer(caption_buffer &&) = default;

        ~caption_buffer();


        void set_text(const std::string &text);
        void set_color(const glm::vec3 &color);
        void set_text_color(const glm::vec3 &color);
        void set_width(int width);
        void set_height(int height);

        void render();

        const std::string &get_text() const { return text; }
        const glm::vec3 &get_color() const { return color; }
        const glm::vec3 &get_text_color() const { return text_color; }
        int get_width() const { return width; }
        int get_height() const { return height; }

        GLuint get_texture_handle();

    private:
        void render(int code, int x, int y, int width, int height);

        font_builder *builder;

        GLuint texhandle;

        std::string text;
        glm::vec3 color;
        glm::vec3 text_color;
        int width;
        int height;

        bool dirty;
        bool resized;
    };
}

#endif
