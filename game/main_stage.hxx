/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_main_stage_hxx
#define __game_main_stage_hxx

#include <putgame/common>
#include <putgame/world>

namespace game
{
    class main_menu;

    class main_stage : public common::context::object
    {
    public:
        using object_ref = std::shared_ptr<world::visible_object>;

        main_stage(common::context *ctx);
        ~main_stage();

        void on_draw();

        void register_object(object_ref ref);
        void delete_unreachable_objects();
        void delete_all_objects();

    private:
        std::shared_ptr<main_menu> menu_ptr;
        std::set<object_ref> object_set;
    };
}

#endif
