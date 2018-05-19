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
    {}

    void tunnel_path::reset()
    {
        auto way = get_part<way_path>();
        auto camid = way->get_camera_frame();
        auto matrix = way->point(camid).get_matrix();

        path_line::reset_matrix(matrix);
    }

    void tunnel_path::update()
    {
        reset_if_empty();

        auto way = get_part<way_path>();

        auto range = get_part<camera>()->get_view_range();
        auto sqrange = range * range;
        auto campos = get_part<camera>()->get_position();

        while (math::sqdist(last_point().get_position(), campos) < sqrange)
        {
            std::cout << "generate!" << std::endl;
            auto new_id = way_frame_id + way_frame_step;
            auto max_id = way->last_point().get_index();

            if (new_id > max_id)
            {
                std::cout << "too big id" << std::endl;
                break;
            }

            way_frame_id = new_id;

            append(way->point(new_id));
        }
    }
}
