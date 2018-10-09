/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_autopilot_hxx
#define __game_autopilot_hxx

#include <putgame/common>

namespace game
{
    class player;

    class autopilot : public common::context::object
    {
    public:
        autopilot(player *pl);

        void correct(float momfactor);
        void correct();
        void reset();

    private:
        float xmom;
        float ymom;
    };
}

#endif
