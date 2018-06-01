/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "exception.hxx"

namespace glutils
{
    location_error::location_error(const std::string &tag,
                                   const std::string &name)
        : tag(tag)
        , name(name)
    {}
}

std::ostream &operator<<(std::ostream &os, 
                         const glutils::location_error &err)
{
    return os << err.tag << ": " << err.name;
}
