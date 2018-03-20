/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "pathway.hxx"

namespace world
{
    pathway::pathway(context *ctx)
        : context_part(ctx)
    {
        points.push_back(point(glm::mat4(1), 0));

        for (int i = 0; i < 200; i++)
            append(PI / 90, { 0, 1, 0 });
    }

    void pathway::append(float angle, const glm::vec3 &axis)
    {
        auto last = get_last();

        auto transform = last.get_matrix();

        transform = glm::rotate(transform, angle, axis);
        transform = glm::translate(transform, glm::vec3(0, 0, step));

        auto index = last.get_index() + 1;

        auto point = glm::vec3(transform * glm::vec4(0, 0, 0, 1));

        std::cout << "generated point at: " 
            << point.x << ", " << point.y << ", " << point.z
            << std::endl;


        points.emplace_back(std::move(transform), index);
    }

    const pathway::point &pathway::get_by_id(int id) const
    {
        id -= points.front().get_index();

        return points[id];
    }

    pathway::point::point(glm::mat4 &&matrix, int index)
        : matrix(matrix)
        , index(index)
    {}
}
