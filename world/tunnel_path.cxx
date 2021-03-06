/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

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
    {
        tunnel_path::reset();
    }

    void tunnel_path::generate_back()
    {
        auto new_id = way_frame_id + way_frame_step;
        auto point = get<way_path>()->at(new_id);

        way_frame_id = new_id;

        append(point);
    }

    void tunnel_path::reset()
    {
        auto camid = get<camera>()->get_frame_id();
        auto matrix = get<way_path>()->at(camid).matrix();

        path_line::reset(matrix);
    }

    void tunnel_path::update()
    {
        try {
            while (true)
                generate_back();
        } catch (no_point) {}

        auto camid = get<camera>()->get_frame_id();
        auto campos = get<camera>()->get_position();

        auto sqremdist = 2 * 4;

        while (not empty()
                and front().index() < camid 
                and math::sqdist(campos, front().matrix()) > sqremdist)
        {
            remove_front();
        }
    }
}
