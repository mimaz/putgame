/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_object_manager_hxx
#define __world_object_manager_hxx

#include "context_part.hxx"

namespace world
{
      template<typename _Object, typename _View>
    class object_manager : public context_part
    {
    public:
        object_manager(context *ctx);

        void add(_Object *obj);
        void remove(_Object *obj);

        void draw_all();

        _View *get_view();

    protected:
        void clear_view();

        virtual _View *new_view() = 0;

    private:
        std::shared_ptr<_View> view;
        std::set<_Object *> objects;
    };
}

#endif
