/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "context_part.hxx"

namespace world
{
    context_part::context_part(context *ctx)
        : _m_context(ctx)
    {}

    context_part::~context_part()
    {}
}
