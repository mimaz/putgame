/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "glass_manager.hxx"

#include "glass_view.hxx"
#include "glass_piece.hxx"

namespace world
{
    glass_manager::glass_manager(context *ctx)
        : context_part(ctx)
        , view(std::make_shared<glass_view>(ctx))
    {}

    void glass_manager::add(glass_pane *pane)
    {
        panes.insert(pane);
    }

    void glass_manager::add(glass_piece *piece)
    {
        pieces.insert(piece);
    }

    void glass_manager::remove(glass_pane *pane)
    {
        panes.erase(pane);
    }

    void glass_manager::remove(glass_piece *piece)
    {
        pieces.erase(piece);
    }

    void glass_manager::draw_all()
    {
        for (auto piece : pieces)
            piece->on_draw();

        draw(false);
        draw(true);
    }

    void glass_manager::draw(bool specular)
    {
        view->begin(specular);


        view->bind_pane(specular);

        for (auto pane : panes)
            view->draw(pane, specular);


        view->bind_piece(specular);

        for (auto piece : pieces)
            view->draw(piece, specular);


        view->end(specular);
    }
}
