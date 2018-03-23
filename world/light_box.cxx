/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>
#include <putgame-res>

#include <glutils/program.hxx>
#include <glutils/shader.hxx>
#include <glutils/attribute.hxx>
#include <glutils/uniform.hxx>
#include <glutils/buffer.hxx>

#include <common/rgb_color.hxx>
#include <common/exception.hxx>

#include "light_box.hxx"

#include "draw_manager.hxx"
#include "context_part.hxx"
#include "context.hxx"
#include "camera.hxx"
#include "lighting.hxx"


constexpr auto size = 1.0f;

namespace 
{
    common::rgb_color to_rgb(world::light_box::color col, 
                             float bright, float dim)
    {
        switch (col)
        {
            case world::light_box::red:
                return common::rgb_color(bright, dim, dim);

            case world::light_box::green:
                return common::rgb_color(dim, bright, dim);

            case world::light_box::blue:
                return common::rgb_color(dim, dim, bright);
        }

        throw common::make_invalid_argument(col);
    }
}

namespace world
{
    light_box::light_box(context *ctx, color col)
        : visible_object(ctx)
        , light_source(ctx)
        , light_col(common::rgb_color::black)
        , surface_col(common::rgb_color::black)
        , speed(0.05)
        , blur(0)
    {
        get_context()->get_part<draw_manager>()->add(this);

        set_color(col);

        rotate(PI * rand() / RAND_MAX);
    }

    light_box::~light_box()
    {
        get_context()->get_part<draw_manager>()->remove(this);
    }

    void light_box::set_color(color c)
    {
        col = c;

        light_col = to_rgb(c, 1.0f, 0.25f);
        surface_col = to_rgb(c, 1.0f, 0.6f);
    }

    void light_box::set_speed(float spd)
    {
        speed = spd;
    }

    void light_box::rotate()
    {
        rotate(get_speed());
    }

    void light_box::rotate(float angle)
    {
        auto speedx = angle;
        auto speedy = angle / 2;

        visible_object::rotate(speedx, { 1, 0, 0 });
        visible_object::rotate(speedy, { 0, 1, 0 });
    }

    common::rgb_color light_box::get_surface_color() const
    {
        return surface_col;
    }

    glm::vec3 light_box::get_light_position() 
    {
        return get_position();
    }

    glm::vec3 light_box::get_light_color()
    {
        return light_col;
    }

    float light_box::get_light_range()
    {
        return 50;
    }
}
