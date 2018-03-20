/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "path_line.hxx"

namespace world
{
    path_line::path_line(float gap)
        : gap(gap)
    {}

    void path_line::append()
    {
        append(0, { 1, 0, 0 });
    }

    void path_line::append(float angle, const glm::vec3 &axis)
    {
        auto matrix = glm::mat4(1);
        auto index = 0;


        if (not points.empty())
        {
            matrix = get_last_point().get_matrix();
            index = get_last_point().get_index() + 1;
        }


        matrix = glm::translate(matrix, glm::vec3(0, 0, gap));
        matrix = glm::rotate(matrix, angle, axis);


        points.emplace_back(matrix, index);
    }

    const path_point &path_line::get_point(int id) const
    {
        return points[id - points.front().get_index()];
    }
}
