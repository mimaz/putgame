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

        auto box = std::make_shared<world::light_box>
            (ctx, 50, world::light_box::white);

        box->translate(glm::vec3(0.5, 0, 0));

        register_object(box);
    }

    main_stage::~main_stage()
    {
        std::cout << "destroy main stage" << std::endl;
    }

    void main_stage::on_draw()
    {
        std::cout << "on draw main_stage" << std::endl;
    }

    void main_stage::register_object(object_ref ref)
    {
        object_set.insert(ref);
    }

    void main_stage::delete_unreachable_objects()
    {

    }

    void main_stage::delete_all_objects()
    {
        object_set.clear();
    }
}
