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

#include "tunnel_view.hxx"

namespace world
{
    tunnel::tunnel(context *ctx)
        : context_part(ctx)
        , view(nullptr)
        , width(2)
        , quality(12)
        , stripped(false)
    {}

    void tunnel::draw()
    {
        get_view()->draw();
    }

    void tunnel::set_width(int wid)
    {
        if (wid != get_width())
        {
            width = wid;

            view = nullptr;
        }
    }

    void tunnel::set_quality(int qual)
    {
        if (qual != get_quality())
        {
            quality = qual;

            view = nullptr;
        }
    }

    void tunnel::set_stripped(bool strip)
    {
        if (strip != is_stripped())
        {
            stripped = strip;

            view = nullptr;
        }
    }

    tunnel_view *tunnel::get_view()
    {
        if (view == nullptr)
        {
            view = std::make_shared<tunnel_view>(
                    2, get_quality(), 
                    is_stripped(), this);
        }

        return view.get();
    }
}
