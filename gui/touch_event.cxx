/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/common>

#include "touch_event.hxx"

namespace gui
{
    touch_event::touch_event(event_type type, int x, int y)
        : type(type), xpos(x), ypos(y) {}
}

std::ostream &operator<<(std::ostream &os, 
                         gui::touch_event::event_type ev)
{
    switch (ev)
    {
        case gui::touch_event::press:
            return os << "press";

        case gui::touch_event::move:
            return os << "move";

        case gui::touch_event::release:
            return os << "release";

        default:
            throw common::make_invalid_argument(ev);
    }
}

std::ostream &operator<<(std::ostream &os, 
                         const gui::touch_event &ev)
{
    return os << ev.type << " " << ev.xpos << ":" << ev.ypos;
}
