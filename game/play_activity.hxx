/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_play_activity_hxx
#define __game_play_activity_hxx

#include <putgame/common>
#include <putgame/world>

#include "player.hxx"
#include "object_generator.hxx"
#include "hit_mask.hxx"

namespace game
{
    class play_activity : public common::context::object
    {
    public:
        using object_ref = std::shared_ptr<world::visible_object>;

        play_activity(common::context *ctx);

        void steer(float x, float y);
        void process();

          template<typename _T, typename ..._Args>
        std::shared_ptr<_T> create_object(const _Args &...args);

        int get_distance();

        player *get_player()  
        { return &player_obj; }

        object_generator *get_object_generator()  
        { return &object_generator_obj; }

        hit_mask *get_hit_mask() 
        { return &hit_mask_obj; }

    private:
        void break_pane(world::glass_pane *pane);

        std::deque<object_ref> object_queue;

        player player_obj;
        object_generator object_generator_obj;
        hit_mask hit_mask_obj;

        int last_way_id;
    };

      template<typename _T, typename ..._Args>
    std::shared_ptr<_T>
    play_activity::create_object(const _Args &...args)
    {
        auto obj = std::make_shared<_T>(args...);

        object_queue.push_back(obj);

        return obj;
    }
}

#endif
