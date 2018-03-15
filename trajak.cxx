/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std.hxx>

#include "trajak.hxx"

namespace world
{
    trajak::trajak(context *ctx)
        : context_part(ctx)
    {}

    void trajak::draw()
    {
        std::cout << "draw!" << std::endl;
    }
}
