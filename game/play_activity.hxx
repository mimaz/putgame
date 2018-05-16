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
    class play_activity : public common::context::object
    {
    public:
        using object_ref = std::shared_ptr<world::visible_object>;

        play_activity(common::context *ctx);
        ~play_activity();

        void on_draw();

        void register_object(const object_ref &ref);

          template<typename _T, typename ..._Args>
        std::shared_ptr<_T> &&create_object(const _Args &...args);

    private:
        std::set<object_ref> object_set;
    };

      template<typename _T, typename ..._Args>
    std::shared_ptr<_T> &&
    play_activity::create_object(const _Args &...args)
    {
        auto obj = std::make_shared<_T>(args...);

        register_object(obj);

        return std::move(obj);
    }
}

#endif
