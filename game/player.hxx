/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_player_hxx
#define __game_player_hxx

#include <putgame/common>

namespace game
{
    class play_activity;
    class autopilot;

    class player : public common::context::object
    {
    public:
        class axis_correction;

        player(play_activity *activity);

        void process();

        void set_autopilot(bool ap);

        int get_frame_id();

    private:
        void test_collision();

        std::shared_ptr<autopilot> apilot;
        play_activity *activity;
    };
}

#endif
