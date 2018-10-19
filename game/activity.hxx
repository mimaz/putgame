/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_activity_hxx
#define __game_activity_hxx

#include <putgame/common>
#include <putgame/world>

#include "player.hxx"
#include "object_generator.hxx"
#include "hit_mask.hxx"
#include "tunnel_generator.hxx"

namespace game
{
    class activity : public common::context::object
    {
    public:
        enum state
        {
            splash,
            menu,
            play,
            defeated,
        };

        using object_ref = std::shared_ptr<world::visible_object>;

        activity(common::context *ctx);

        void steer(float x, float y);
        void process();

        void switch_state(state st);

          template<typename _T, typename ..._Args>
        std::shared_ptr<_T> create_object(const _Args &...args);

        state get_state() const;
        bool is_transiting() const;

        int get_distance();
        int get_difficulty();

        player *get_player();
        hit_mask *get_hit_mask();

    private:
        void break_pane(world::glass_pane *pane);

        std::deque<object_ref> object_queue;

        int last_way_id;
        int last_distance;
        int last_difficulty;

        state stat;
        bool transiting;
    };

      template<typename _T, typename ..._Args>
    std::shared_ptr<_T>
    activity::create_object(const _Args &...args)
    {
        auto obj = std::make_shared<_T>(args...);

        object_queue.push_back(obj);

        return obj;
    }
}

#endif
