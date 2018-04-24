/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>
#include <putgame/math>

#include "path_point.hxx"

namespace world
{
    glm::vec3 path_point::get_position() const
    {
        return math::coord3d(get_matrix());
    }

    path_point::operator glm::mat4() const
    {
        return get_matrix();
    }
}

std::ostream &operator<<(std::ostream &os, const world::path_point &pt)
{
    return os << "point" << math::coord3d(pt.get_matrix());
}
