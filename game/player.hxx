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

    class player : public common::context::object
    {
    public:
        player(play_activity *activity);

        void set_autopilot(bool ap);

        void on_draw();

        int get_frame_id();

    private:
        void correct_direction(glm::vec3 target);

        play_activity *activity;
        bool autopilot;
        float correction_momentum;
    };
}

#endif
