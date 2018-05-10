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
    tunnel_path::tunnel_path(way_path *way, float gap)
        : path_line(gap)
        , way(way)
        , way_back_id(0)
    {
        for (int i = 0; i < 10; i++)
            gen_frame_back();
    }

    void tunnel_path::gen_frame_back()
    {
        if (get_points().empty())
        {
            reset(way->get_first_point().get_matrix());
            return;
        }

        auto too_close = [this](int id, const path_point &pt) -> bool {
            auto pv = way->get_point(id).get_position();
            auto qv = pt.get_position();

            return glm::distance(pv, qv) < get_gap();
        };

        while (too_close(way_back_id, get_last_point()))
            way_back_id++;

        append(way->get_point(way_back_id));
    }
}
