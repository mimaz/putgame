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

        void register_object(object_ref ref);
        void delete_unreachable_objects();
        void delete_all_objects();

    private:
        std::set<object_ref> object_set;
    };
}

#endif
