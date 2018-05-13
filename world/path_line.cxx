/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>
#include <putgame/math>

#include "path_line.hxx"

namespace world
{
    constexpr auto start_id = 0;

    path_line::path_line(common::context *ctx, float gap)
        : object(ctx)
        , gap(gap)
    {}

    void path_line::append(float angle, glm::vec3 axis)
    {
        auto matrix = make_matrix(angle, axis);
        auto index = start_id;

        if (not points.empty())
        {
            auto last = get_last_point();

            matrix *= last.get_matrix();
            index = last.get_index() + 1;
        }

        points.emplace_back(matrix, index);
    }

    void path_line::append(const glm::mat4 &mat)
    {
        int index;

        if (points.empty())
            index = start_id;
        else
            index = get_last_point().get_index() + 1;

        points.emplace_back(mat, index);
    }

    void path_line::remove_back()
    {
        points.pop_back();
    }

    void path_line::remove_front()
    {
        points.pop_front();
    }

    void path_line::reset(const glm::mat4 &matrix)
    {
        points.clear();
        points.emplace_back(matrix, 0);
    }

    const path_point &path_line::get_first_point() const
    { 
        return get_points().front();
    }

    const path_point &path_line::get_last_point() const
    { 
        return get_points().back();
    }

    const std::deque<path_point> &path_line::get_points() const
    {
        return points;
    }

    const path_point &path_line::get_point(int id) const
    {
        return points[id - points.front().get_index()];
    }

    int path_line::updated_id(const glm::mat4 &mat, int id) const
    {
        return updated_id(math::coord3d(mat), id);
    }

    int path_line::updated_id(glm::vec3 coord, int id) const
    {
        auto dist = [coord, this](int i) -> float {
            auto mat = get_point(i).get_matrix();

            return math::sqdist(coord, mat);
        };

        auto cdst = dist(id);

        if (id > get_first_point().get_index() and dist(id - 1) < cdst)
            return id - 1;

        if (id < get_last_point().get_index() and dist(id + 1) < cdst)
            return id + 1;

        return id;
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
