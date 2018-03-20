/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

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
    tunnel_path::tunnel_path(path_line *pattern, float gap)
        : path_line(gap)
        , pattern(pattern)
        , pattern_id(0)
    {
        for (int i = 0; i < 10; i++)
            gen_frame();
    }

    void tunnel_path::gen_frame()
    {
        if (get_points().empty())
        {
            append();
            return;
        }


        auto calc_target_coord = [this](void) -> glm::vec3 {
            auto mat = pattern->get_point(pattern_id).get_matrix();

            return get_position(mat);
        };


        auto last_coord = get_position(get_last_point().get_matrix());
        auto target_coord = calc_target_coord();



        while (glm::length(target_coord - last_coord) < get_gap())
        {
            pattern_id++;
            target_coord = calc_target_coord();
        }



        auto last_direction = glm::normalize(
            get_direction(get_last_point().get_matrix())
        );

        auto new_direction = glm::normalize(
            target_coord - last_coord
        );

        auto axis = glm::normalize(
            glm::cross(last_direction, new_direction)
        );

        auto angle = acosf(
            glm::dot(new_direction, last_direction)
        );


        append(angle, axis);
    }
}
