/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __text_font_builder_hxx
#define __text_font_builder_hxx

namespace text
{
    using point = glm::vec2;
    using segment = std::pair<point, point>;

    class font_builder
    {
    public:
        class char_desc;

        using data_map = std::map<int, char_desc>;

        font_builder(float thickness,
                     int width, int height, 
                     const data_map &font_data);
        ~font_builder();

        void bind_texture(int code);

    private:
        GLuint textures[128];
    };

    class font_builder::char_desc
    {   
    public:
        const char *map;
        const char *order;
    };
}

#endif
