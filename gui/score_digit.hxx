/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __gui_score_digit_hxx
#define __gui_score_digit_hxx

#include "rect_item.hxx"

namespace gui
{
    class score_digit : rect_item
    {
    public:
        void draw() override;
        void process() override;

    private:
    };
}

#endif
