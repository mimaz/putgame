/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/res>
#include <putgame/math>
#include <putgame/common>

#include "light_box.hxx"

#include "object_manager.hxx"
#include "camera.hxx"
#include "lighting.hxx"

namespace 
{
    glm::vec3 to_rgb(world::light_box::color col, 
                     float bright, float dim)
    {
        switch (col)
        {
            case world::light_box::red:
                return glm::vec3(bright, dim, dim);

            case world::light_box::green:
                return glm::vec3(dim, bright, dim);

            case world::light_box::blue:
                return glm::vec3(dim, dim, bright);

            default:
                throw common::make_invalid_argument(col);
        }
    }

    world::light_box::color random_color(common::context *ctx)
    {
        std::uniform_int_distribution<int> dist
            (0, world::light_box::color_count - 1);

        auto idx = dist(ctx->get_random_engine());

        return static_cast<world::light_box::color>(idx);
    }
}

namespace world
{
    light_box::light_box(common::context *ctx, int frameid)
        : light_box(ctx, frameid, random_color(ctx))
    {}

    light_box::light_box(common::context *ctx, int frameid, color col)
        : visible_object(ctx, frameid)
        , light_source(ctx)
        , light_col(common::black3())
        , surface_col(common::black3())
        , speedx(rand_speed())
        , speedy(rand_speed())
        , speedz(rand_speed())
    {
        get<object_manager>()->add(this);

        set_color(col);
    }

    light_box::~light_box()
    {
        get<object_manager>()->remove(this);
    }

    void light_box::set_color(color c)
    {
        col = c;

        light_col = to_rgb(c, 1.0f, 0.25f);
        surface_col = to_rgb(c, 1.0f, 0.6f);
    }

    void light_box::process()
    {
        visible_object::rotate(speedx, { 0, 1, 0 });
        visible_object::rotate(speedy, { 1, 0, 0 });
        visible_object::rotate(speedz, { 0, 0, 1 });
    }

    glm::vec3 light_box::get_surface_color() const
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
        return 8;
    }

    float light_box::rand_speed()
    {
        std::normal_distribution<float> dist(0.0f, 1.0f);

        auto rand = dist(get_random_engine()) * 0.02f;

        if (rand < 0)
            return rand - 0.05f;

        return rand + 0.04f;
    }
}
