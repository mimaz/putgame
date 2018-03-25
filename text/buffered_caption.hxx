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
        void set_color(const glm::vec3 &color);
        void set_text_color(const glm::vec3 &color);
        void set_width(int width);
        void set_height(int height);
        void set_font_size(float size);

        void render();

        const std::string &get_text() const { return text; }
        const glm::vec3 &get_color() const { return color; }
        const glm::vec3 &get_text_color() const { return text_color; }
        int get_width() const { return width; }
        int get_height() const { return height; }
        float get_font_size() const { return font_size; }

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
        float font_size;

        bool dirty;
        bool resized;
    };
}

#endif
