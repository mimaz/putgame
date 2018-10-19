/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __gui_score_counter_hxx
#define __gui_score_counter_hxx

#include <putgame/text>

#include "rect_item.hxx"

namespace gui
{
    class score_counter : rect_item
    {
    public:
        score_counter(common::context *ctx);

        void set_value(int value);

        void draw() override;
        void process() override;

        int get_value() const;

    private:
        int current_value;
        int value;

        text::text_buffer text;
    };
}

#endif
