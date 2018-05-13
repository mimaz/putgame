/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_main_stage_hxx
#define __game_main_stage_hxx

#include <putgame/common>

namespace game
{
    class main_menu;

    class main_stage : public common::context::object
    {
    public:
        main_stage(common::context *ctx);
        ~main_stage();

        void on_draw();

    private:
        std::shared_ptr<main_menu> menu_ptr;
    };
}

#endif
