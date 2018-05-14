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
        if (empty())
            reset();

        auto last = last_point();
        auto matrix = last.get_matrix() * make_matrix(angle, axis);
        auto index = last.get_index() + 1;

        pointv.emplace_back(matrix, index);
    }

    void path_line::append(const glm::mat4 &mat)
    {
        auto index = last_point().get_index() + 1;

        pointv.emplace_back(mat, index);
    }

    void path_line::remove_back()
    {
        pointv.pop_back();
    }

    void path_line::remove_front()
    {
        pointv.pop_front();
    }

    void path_line::reset_if_empty()
    {
        if (empty())
            reset();
    }

    void path_line::reset_matrix(const glm::mat4 &matrix)
    {
        pointv.clear();
        pointv.emplace_back(matrix, 0);
    }

    const path_point &path_line::first_point() const
    { 
        if (pointv.empty())
            throw no_point();

        return pointv.front();
    }

    const path_point &path_line::last_point() const
    { 
        if (pointv.empty())
            throw no_point();

        return pointv.back();
    }

    const std::deque<path_point> &path_line::points() const
    {
        return pointv;
    }

    const path_point &path_line::point(int id) const
    {
        if (id < first_point().get_index() 
                or id > last_point().get_index())
        {
            throw no_point();
        }

        auto off = id - first_point().get_index();

        return pointv[off];
    }

    int path_line::updated_id(const glm::mat4 &mat, int id) const
    {
        return updated_id(math::coord3d(mat), id);
    }

    int path_line::updated_id(glm::vec3 coord, int id) const
    {
        auto dist = [coord, this](int i) -> float {
            auto mat = point(i).get_matrix();

            return math::sqdist(coord, mat);
        };

        auto cdst = dist(id);

        if (id > first_point().get_index() and dist(id - 1) < cdst)
            return id - 1;

        if (id < last_point().get_index() and dist(id + 1) < cdst)
            return id + 1;

        return id;
    }

    glm::mat4 path_line::make_matrix(float angle, glm::vec3 axis) const
    {
        glm::mat4 matrix(1);
        glm::vec3 offset(0, 0, -gap);

        matrix = glm::rotate(matrix, angle, axis);
        matrix = glm::translate(matrix, offset);

        return matrix;
    }
}
