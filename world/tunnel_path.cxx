/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "tunnel_path.hxx"

#include "way_path.hxx"

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
        , way_back_id(0)
    {}

    void tunnel_path::reset()
    {
        auto way = get_part<way_path>();
        auto camid = way->get_camera_frame();
        auto matrix = way->get_point(camid).get_matrix();

        path_line::reset(matrix);
    }

    void tunnel_path::update()
    {
        std::cout << "process" << std::endl;
    }

    void tunnel_path::gen_frame_back()
    {
        auto way = get_part<way_path>();

        if (get_points().empty())
            reset();

        auto too_close = [this, way]
                         (int id, const path_point &pt) -> bool {
            auto pv = way->get_point(id).get_position();
            auto qv = pt.get_position();

            return glm::distance(pv, qv) < get_gap();
        };

        while (too_close(way_back_id, get_last_point()))
            way_back_id++;

        append(way->get_point(way_back_id));
    }
}
