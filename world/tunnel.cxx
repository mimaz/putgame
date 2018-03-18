/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>
#include <putgame-res>

#include <glutils/shader.hxx>
#include <glutils/program.hxx>
#include <glutils/uniform.hxx>
#include <glutils/attribute.hxx>

#include "tunnel.hxx"

#include "tunnel_model.hxx"

namespace world
{
    tunnel::tunnel(context *ctx)
        : context_part(ctx)
        , model(std::make_shared<tunnel_model>(2, 10, false, this))
    {}

    void tunnel::draw()
    {
        model->draw();
    }
}
