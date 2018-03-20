/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "glass_piece.hxx"

#include "glass_pane.hxx"
#include "glass_manager.hxx"
#include "context.hxx"

namespace 
{
    float random_float()
    {
        return static_cast<float>(rand()) / RAND_MAX;
    }

    float random_speed()
    {

        return PI / (60 + random_float() * 40);
    }

    glm::vec3 random_axis()
    {
        return glm::vec3(1, random_float(), random_float());
    }

    float random_scale()
    {
        return random_float() * 0.1 + 0.07;
    }
}

namespace world
{
    glass_piece::glass_piece(glass_pane *pane)
        : visible_object(pane->get_context())
        , color(pane->get_color())
        , rotation_speed(random_speed())
        , rotation_axis(random_axis())
    {
        get_context()->get_part<glass_manager>()->add(this);

        scale(random_scale());
    }

    glass_piece::~glass_piece()
    {
        get_context()->get_part<glass_manager>()->remove(this);
    }

    void glass_piece::on_draw()
    {
        rotate(rotation_speed, rotation_axis);
    }
}
