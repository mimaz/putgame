/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/math>

#include "tunnel_path.hxx"

#include "way_path.hxx"
#include "camera.hxx"

namespace 
{
    inline glm::vec3 get_position(const glm::mat4 &matrix)
    {
        return glm::vec3(matrix * glm::vec4(0, 0, 0, 1));
    }

    inline glm::vec3 get_direction(const glm::mat4 &matrix)
    {
        return glm::vec3(matrix * glm::vec4(0, 0, 1, 0));
    }

    inline int frame_hash(const glm::mat4 &matrix, int index)
    {
        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++)
                index += static_cast<int>(matrix[y][x]);

        return std::hash<int>()(rand() + index);
    }
}

namespace world
{
    tunnel_path::tunnel_path(common::context *ctx, float gap)
        : path_line(ctx, gap)
        , way_frame_id(0)
        , way_frame_step(static_cast<int>
                (gap / ctx->get_part<way_path>()->get_gap()))
    {
        reset();
    }

    void tunnel_path::reset()
    {
        auto way = get_part<way_path>();
        auto camid = way->get_camera_frame();
        auto matrix = way->get_point(camid).get_matrix();

        path_line::reset(matrix);
    }

    void tunnel_path::update()
    {
        if (get_points().empty())
            reset();

        auto way = get_part<way_path>();
        auto range = get_part<camera>()->get_view_range();
        auto campos = get_part<camera>()->get_position();
        auto lastpos = get_last_point().get_position();

        while (glm::distance(campos, lastpos) < range)
        {
            auto new_id = way_frame_id + way_frame_step;
            auto max_id = way->get_last_point().get_index();

            if (new_id > max_id)
                break;

            way_frame_id = new_id;

            append(way->get_point(new_id));
        }
    }
}
