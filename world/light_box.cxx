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

#include "light_box_manager.hxx"
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
        , manager(ctx->get_part<light_box_manager>())
        , speed(0.05)
        , angle(PI * 2 * rand() / RAND_MAX)
        , blur(0)
    {
        manager->register_box(this);

        set_color(col);
    }

    light_box::~light_box()
    {
        manager->unregister_box(this);
    }

    void light_box::set_color(color c)
    {
        col = c;

        light_col = to_rgb(c, 1.0f, 0.25f);
        surface_col = to_rgb(c, 1.0f, 0.75f);
    }

    void light_box::set_speed(float spd)
    {
        speed = spd;
    }

    void light_box::on_draw()
    {
        angle += get_speed();
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
        return manager->get_light_range();
    }
}
