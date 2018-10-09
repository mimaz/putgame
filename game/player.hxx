/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_player_hxx
#define __game_player_hxx

#include <putgame/common>

namespace game
{
    class autopilot;

    class player : public common::context::object
    {
    public:
        class axis_correction;

        player(common::context *ctx);

        void steer(float x, float y);
        void process();

        void set_autopilot(bool ap);
        void set_target_speed(float speed);

        int get_frame_id() const;
        float get_target_speed() const;
        float get_real_speed() const;

    private:
        bool test_collision();

        std::shared_ptr<autopilot> apilot;
        bool apilot_enabled;

        float target_speed;
        float real_speed;
    };
}

#endif
