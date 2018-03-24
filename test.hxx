#ifndef __test_hxx
#define __test_hxx

#include <putgame/glutils>
#include <putgame/text>

class test
{
public:
    test();

    void draw(text::font_builder *builder);

private:
    glutils::shader vsh;
    glutils::shader fsh;
    glutils::program pro;
    glutils::attribute a_coord;
    glutils::attribute a_tex_coord;
    glutils::uniform u_texture;
};

#endif
