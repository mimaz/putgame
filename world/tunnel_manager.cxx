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

#include "tunnel_manager.hxx"

#include "tunnel_view.hxx"
#include "tunnel_path.hxx"
#include "context.hxx"

namespace world
{
    tunnel_manager::tunnel_manager(context *ctx)
        : context_part(ctx)
        , view(nullptr)
        , width(2)
        , quality(16)
    {}

    void tunnel_manager::draw_all()
    {
        get_view()->draw();
    }

    void tunnel_manager::clear()
    {
        get_view()->get_path()->reset();
    }

    void tunnel_manager::set_width(int wid)
    {
        if (wid != get_width())
        {
            width = wid;

            view = nullptr;
        }
    }

    void tunnel_manager::set_quality(int qual)
    {
        if (qual != get_quality())
        {
            quality = qual;

            view = nullptr;
        }
    }

    tunnel_view *tunnel_manager::get_view()
    {
        if (view == nullptr)
        {
            view = std::make_shared<tunnel_view>(
                    2, get_quality(), 
                    get_context());
        }

        return view.get();
    }
}
