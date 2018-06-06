/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __gui_hit_mask_hxx
#define __gui_hit_mask_hxx

#include "rect_item.hxx"

namespace gui
{
    class hit_mask : public rect_item
    {
    public:
        hit_mask(common::context *ctx, glm::vec4 col);

        void hit();

        void draw() override;
        void process() override;

        glm::vec4 get_color() const;

    private:
        glm::vec4 color;
        float exposure;
    };
}

#endif
