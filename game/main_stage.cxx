/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "main_stage.hxx"
#include "main_menu.hxx"

namespace game
{
    main_stage::main_stage(common::context *ctx)
        : object(ctx)
    {
        menu_ptr = std::make_shared<main_menu>(ctx);
    }

    main_stage::~main_stage()
    {
        std::cout << "destroy main stage" << std::endl;
    }

    void main_stage::on_draw()
    {
        std::cout << "on draw main_stage" << std::endl;
    }
}
