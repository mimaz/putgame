/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_hit_mask_hxx
#define __game_hit_mask_hxx

#include <putgame/gui>

namespace game
{
    class activity;

    class hit_mask : public gui::color_rectangle
    {
    public:
        hit_mask(common::context *ctx);

        void hit(float cosine);

        void on_surface_resize(int w, int h) override;
        void process() override;

        float get_exposure() const;

    private:
        float exposure;
    };
}

#endif
