/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>

#include "path_point.hxx"

namespace world
{
    glm::vec3 path_point::get_position() const
    {
        return common::position(get_matrix());
    }

    path_point::operator glm::mat4() const
    {
        return get_matrix();
    }
}

std::ostream &operator<<(std::ostream &os, const world::path_point &pt)
{
    return os << "point" << common::position(pt.get_matrix());
}
