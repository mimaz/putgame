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
        class character_recipe;

        font_builder(const character_recipe *recipes, 
                     int recipe_count);
        ~font_builder();

        void bind_texture(int code);

    private:
        GLuint textures[128];
    };

    class font_builder::character_recipe
    {
    public:
        std::vector<point> points;
        std::vector<segment> segments;
        int code;
    };
}

#endif
