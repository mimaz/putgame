/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/common>
#include <putgame/math>

#include "path_point.hxx"

namespace world
{
    path_point::path_point(const glm::mat4 &matrix, int index)
        : mat(matrix)
        , idx(index)
    {}

    const glm::mat4 &path_point::matrix() const 
    { 
        return mat; 
    }

    glm::vec3 path_point::position() const
    {
        return math::coord3d(matrix());
    }

    int path_point::index() const
    { 
        return idx; 
    }

    path_point::operator glm::mat4() const
    {
        return matrix();
    }
}

std::ostream &operator<<(std::ostream &os, const world::path_point &pt)
{
    return os << "point" << math::coord3d(pt.matrix());
}
