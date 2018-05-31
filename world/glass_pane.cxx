/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "glass_pane.hxx"

#include "object_manager.hxx"
#include "constants.hxx"
#include "way_path.hxx"

namespace world
{
    glass_pane::glass_pane(common::context *ctx,
                           int frameid,
                           glm::vec3 col)
        : glass_pane(ctx, frameid, col, tunnel_square_area)
    {}

    glass_pane::glass_pane(common::context *ctx,
                           int frameid,
                           glm::vec3 col, 
                           glm::vec2 siz)
        : visible_object(ctx, frameid)
        , color(col)
        , size(siz)
    {
        scale(siz.x, siz.y, 1.0f);

        get<object_manager>()->add(this);
    }

    glass_pane::~glass_pane()
    {
        get<object_manager>()->remove(this);
    }

    glm::mat4 glass_pane::get_piece_matrix() const
    {
        auto scale_vec = glm::vec3(get_size(), 1.0f);
        auto scale_mat = glm::scale(glm::mat4(1), scale_vec);
        auto unscale_mat = glm::inverse(scale_mat);

        return get_model() * unscale_mat;
    }
}
