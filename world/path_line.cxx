/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>

#include "path_line.hxx"

namespace world
{
    path_line::path_line(float gap)
        : gap(gap)
    {}

    void path_line::append(float angle, glm::vec3 axis)
    {
        auto matrix = make_matrix(angle, axis);
        auto index = 0;

        if (not points.empty())
        {
            auto last = get_last_point();

            matrix *= last.get_matrix();
            index = last.get_index() + 1;
        }

        points.emplace_back(matrix, index);
        std::cout << "new point: " << glm::vec3(matrix * glm::vec4(0, 0, 0, 1)) << std::endl;
    }

    void path_line::append(const glm::mat4 &mat)
    {
        int index;

        if (points.empty())
            index = 0;
        else
            index = get_last_point().get_index() + 1;

        points.emplace_back(mat, index);
    }

    void path_line::reset(const glm::mat4 &matrix)
    {
        points.clear();
        points.emplace_back(matrix, 0);
    }

    const path_point &path_line::get_point(int id) const
    {
        return points[id - points.front().get_index()];
    }

    glm::mat4 path_line::make_matrix(float angle, glm::vec3 axis) const
    {
        glm::mat4 matrix(1);
        glm::vec3 offset(0, 0, gap);

        matrix = glm::translate(matrix, offset);
        matrix = glm::rotate(matrix, angle, axis);

        return matrix;
    }
}
