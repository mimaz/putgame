/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_light_box_manager_hxx
#define __world_light_box_manager_hxx

#include "context_part.hxx"

namespace world
{
    class light_box;
    class light_box_view;

    class light_box_manager : public context_part
    {
    public:
        light_box_manager(context *ctx);

        void register_box(light_box *box);
        void unregister_box(light_box *box);

        void draw_all();

        void set_stripped(bool stripped);
        void set_light_range(float range);

        bool is_stripped() const { return stripped; }
        float get_light_range() const { return light_range; }

        light_box_view *get_view() const { return view.get(); }

    private:
        std::shared_ptr<light_box_view> view;
        std::set<light_box *> boxes;

        bool stripped;
        float light_range;
    };
}

#endif

