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

namespace game
{
    class activity : public common::context::object
    {
    public:
        using object_ref = std::shared_ptr<world::visible_object>;

        activity(common::context *ctx);

        void steer(float x, float y);
        void process();

          template<typename _T, typename ..._Args>
        std::shared_ptr<_T> create_object(const _Args &...args);

        int get_distance();
        int get_difficulty();

        player *get_player();
        object_generator *get_object_generator();
        hit_mask *get_hit_mask();

    private:
        void break_pane(world::glass_pane *pane);

        std::deque<object_ref> object_queue;

        player play;
        object_generator ogen;
        hit_mask hmsk;

        int last_way_id;
        int last_distance;
        int last_difficulty;
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
