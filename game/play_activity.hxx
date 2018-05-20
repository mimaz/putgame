/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __game_play_activity_hxx
#define __game_play_activity_hxx

#include <putgame/common>
#include <putgame/world>

namespace game
{
    class player;
    class object_generator;

    class play_activity : public common::context::object
    {
    public:
        using object_ref = std::shared_ptr<world::visible_object>;

        play_activity(common::context *ctx);
        ~play_activity();

        void on_draw();

          template<typename _T, typename ..._Args>
        std::shared_ptr<_T> create_object(const _Args &...args);

        player *get_player() const 
        { return player_ref.get(); }

        object_generator *get_object_generator() const 
        { return object_generator_ref.get(); }

    private:
        std::deque<object_ref> object_queue;

        std::shared_ptr<player> player_ref;
        std::shared_ptr<object_generator> object_generator_ref;
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
