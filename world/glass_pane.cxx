/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "glass_pane.hxx"

#include "draw_manager.hxx"

namespace world
{
    glass_pane::glass_pane(common::context *ctx,
                           glm::vec3 col, 
                           glm::vec2 siz)
        : visible_object(ctx)
        , color(col)
        , size(siz)
    {
        scale(siz.x, siz.y, 1.0f);

        get_part<draw_manager>()->add(this);
    }

    glass_pane::~glass_pane()
    {
        get_part<draw_manager>()->remove(this);
    }

    glm::mat4 glass_pane::get_piece_matrix() const
    {
        auto scale_vec = glm::vec3(get_size(), 1.0f);
        auto scale_mat = glm::scale(glm::mat4(1), scale_vec);
        auto unscale_mat = glm::inverse(scale_mat);

        return get_model() * unscale_mat;
    }
}
