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

namespace world
{
    light_box::light_box(context *ctx, color col)
        : visible_object(ctx)
        , light_source(ctx)
        , light_col(common::rgb_color::black)
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

        auto dim = 0.0f;

        switch (c)
        {
        case red:
            light_col = common::rgb_color(1.f, dim, dim);
            break;

        case green:
            light_col = common::rgb_color(dim, 1.0f, dim);
            break;

        case blue:
            light_col = common::rgb_color(dim, dim, 1.0f);
            break;

        default:
            throw common::make_invalid_argument(c);
        }
    }

    void light_box::set_speed(float spd)
    {
        speed = spd;
    }

    void light_box::on_draw()
    {
        angle += get_speed();
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
