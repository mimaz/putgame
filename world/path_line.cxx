/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/common>
#include <putgame/math>

#include "path_line.hxx"

namespace world
{
    constexpr auto start_id = 0;

    path_line::path_line(common::context *ctx, float gap)
        : object(ctx)
        , pointv(1, path_point(glm::mat4(1), 0))
        , gap(gap)
    {}

    void path_line::remove_front()
    {
        pointv.pop_front();
    }

    void path_line::append(float angle, glm::vec3 axis)
    {
        if (empty())
            throw common::invalid_state("path_line empty!");

        glm::vec3 offset(0, 0, -gap);

        auto matrix = glm::rotate(angle, axis);

        matrix = glm::translate(matrix, offset);
        matrix = back().matrix() * matrix;

        append(matrix);
    }

    void path_line::append(const glm::mat4 &mat)
    {
        auto index = back().index() + 1;

        pointv.emplace_back(mat, index);
    }

    void path_line::reset(const glm::mat4 &matrix)
    {
        pointv.clear();
        pointv.emplace_back(matrix, 0);
    }

    const std::deque<path_point> &path_line::points() const
    {
        return pointv;
    }

    const path_point &path_line::front() const
    { 
        if (pointv.empty())
            throw no_point();

        return pointv.front();
    }

    const path_point &path_line::back() const
    { 
        if (pointv.empty())
            throw no_point();

        return pointv.back();
    }

    const path_point &path_line::at(int id) const
    {
        if (id < front().index() 
                or id > back().index())
        {
            throw no_point();
        }

        auto off = id - front().index();

        return pointv[off];
    }

    int path_line::updated_id(const glm::mat4 &mat, int id) const
    {
        return updated_id(math::coord3d(mat), id);
    }

    int path_line::updated_id(glm::vec3 coord, int id) const
    {
        auto dist = [coord, this](int i) -> float {
            auto mat = at(i).matrix();

            return math::sqdist(coord, mat);
        };

        auto cdst = dist(id);

        if (id > front().index() and dist(id - 1) < cdst)
            return id - 1;

        if (id < back().index() and dist(id + 1) < cdst)
            return id + 1;

        return id;
    }
}
