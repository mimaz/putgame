/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std.hxx>

#include "light_box.hxx"

#include "context_part.hxx"
#include "context.hxx"
#include "shader.hxx"
#include "program.hxx"

constexpr auto size = 1.0f;

using common::rgb_color;


namespace 
{
    const GLchar *vcode = R"(
    )";

    const GLchar *fcode = R"(
    )";

    class drawer : public world::context_part
    {
    public:
        drawer(world::context *ctx) 
            : context_part(ctx)
            , vsh(GL_VERTEX_SHADER, vcode)
            , fsh(GL_FRAGMENT_SHADER, fcode)
            , prog(&vsh, &fsh)
        {}

        void draw(world::light_box *box)
        {

        }

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program prog;
    };
}

namespace world
{
    light_box::light_box(context *ctx, rgb_color color)
        : visible_object(ctx)
        , color(color)
        , speed(1)
        , angle(0)
        , blur(0)
    {}

    void light_box::set_color(const common::rgb_color &col)
    {
        color = col;
    }

    void light_box::set_speed(float spd)
    {
        speed = spd;
    }

    void light_box::draw()
    {
        angle += get_speed();

        get_context()->get_part<drawer>()->draw(this);
    }
}
