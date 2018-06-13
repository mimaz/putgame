/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/common>

#include "hit_mask.hxx"

#include "activity.hxx"

namespace game
{
    hit_mask::hit_mask(common::context *ctx)
        : color_rectangle(ctx)
        , exposure(0)
    {
        set_active(false);
        set_depth(150);
        resize(ctx->get_width(), ctx->get_height());
    }

    void hit_mask::hit(float cosine)
    {
        exposure = sqrtf(cosine);

        common::logd("hit!!!");

        set_active(true);
    }

    void hit_mask::on_surface_resize(int w, int h) 
    {
        color_rectangle::on_surface_resize(w, h);

        resize(w, h);
    }

    void hit_mask::process()
    {
        common::logd("exp: ", get_exposure());

        if (exposure < 0.0f)
        {
            set_active(false);
        }
        else
        {
            if (exposure < 2)
                exposure -= 0.5f / FPS;
            else
                exposure = 3;

            auto real = glm::vec4(1, 0, 0, get_exposure());

            set_color(real);
        }
    }

    float hit_mask::get_exposure() const
    {
        return exposure;
    }
}
