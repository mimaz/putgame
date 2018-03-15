/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std.hxx>

#include "context.hxx"
#include "trajak.hxx"

namespace world
{
    context::context()
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    }

    context::~context()
    {}

    void context::draw_frame()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        get_part<trajak>()->draw();
    }
}
