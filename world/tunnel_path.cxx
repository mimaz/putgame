/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/math>

#include "tunnel_path.hxx"

#include "way_path.hxx"
#include "camera.hxx"

namespace world
{
    tunnel_path::tunnel_path(common::context *ctx, float gap)
        : path_line(ctx, gap)
        , way_frame_id(0)
        , way_frame_step(static_cast<int>
                (gap / ctx->get<way_path>()->get_gap()))
    {}

    void tunnel_path::reset()
    {
        auto way = get<way_path>();
        auto camid = way->get_camera_frame();
        auto matrix = way->point(camid).get_matrix();

        path_line::reset_matrix(matrix);
    }

    void tunnel_path::update()
    {
        reset_if_empty();

        auto campos = get<camera>()->get_position();
        auto range = get<camera>()->get_view_range();
        auto sqrange = range * range;

        while (math::sqdist(last_matrix(), campos) < sqrange)
            generate();

        while (math::sqdist(first_matrix(), campos) > sqrange)
            remove_front();
    }

    void tunnel_path::generate()
    {
        auto new_id = way_frame_id + way_frame_step;

        if (new_id > get<way_path>()->last_index())
            throw common::invalid_state("tunnel path cannot be created "
                                        "behind way path!");

        way_frame_id = new_id;

        append(get<way_path>()->point(new_id));
    }
}
