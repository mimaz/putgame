/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "path.hxx"

namespace world
{
    path::path(context *ctx)
        : context_part(ctx)
    {
        segments.push_back(segment(glm::mat4(1), 0));

        for (int i = 0; i < 20; i++)
            append(PI / 90, { 0, 1, 0 });
    }

    void path::append(float angle, const glm::vec3 &axis)
    {
        auto last = get_last();

        auto transform = last.get_matrix();

        transform = glm::rotate(transform, angle, axis);
        transform = glm::translate(transform, glm::vec3(0, 0, step));

        auto index = last.get_index() + 1;

        auto point = glm::vec3(transform * glm::vec4(0, 0, 0, 1));

        std::cout << "segment at point: " 
            << point.x << ", " << point.y << ", " << point.z
            << std::endl;


        segments.emplace_back(std::move(transform), index);
    }

    const path::segment &path::get_by_id(int id) const
    {
        id -= segments.front().get_index();

        return segments[id];
    }

    path::segment::segment(glm::mat4 &&matrix, int index)
        : matrix(matrix)
        , index(index)
    {}
}
