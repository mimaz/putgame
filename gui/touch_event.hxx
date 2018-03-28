/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __gui_touch_event_hxx
#define __gui_touch_event_hxx

namespace gui
{
    class touch_event
    {
    public:
        enum event_type
        {
            press,
            move,
            release,
        };

        touch_event(event_type type, int x, int y)
            : type(type), xpos(x), ypos(y) {}

        event_type type;
        int xpos, ypos;
    };
}

#endif
