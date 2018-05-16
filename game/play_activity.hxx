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

    class play_activity : public common::context::object
    {
    public:
        using object_ref = std::shared_ptr<world::visible_object>;

        play_activity(common::context *ctx);
        ~play_activity();

        void on_draw();

          template<typename _T, typename ..._Args>
        std::shared_ptr<_T> create_object(const _Args &...args);

        game::player *get_player() const { return player.get(); }

    private:
        std::deque<object_ref> object_queue;
        std::shared_ptr<game::player> player;
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
