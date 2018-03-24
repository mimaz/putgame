/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "object_manager.hxx"

#include "glass_pane.hxx"
#include "glass_pane_view.hxx"

#include "light_box.hxx"
#include "light_box_view.hxx"

#include "wall_obstacle.hxx"
#include "wall_obstacle_view.hxx"

namespace world
{
      template<typename _Object, typename _View>
    object_manager<_Object, _View>::object_manager(context *ctx)
        : context::part(ctx)
    {}

      template<typename _Object, typename _View>
    void object_manager<_Object, _View>::add(_Object *obj)
    {
        objects.insert(obj);
    }

      template<typename _Object, typename _View>
    void object_manager<_Object, _View>::remove(_Object *obj)
    {
        objects.erase(obj);
    }

      template<typename _Object, typename _View>
    void object_manager<_Object, _View>::draw_all()
    {
        get_view()->begin_drawing();

        for (auto obj : objects)
        {
            on_draw(obj);

            get_view()->draw_element(obj);
        }

        get_view()->end_drawing();
    }

      template<typename _Object, typename _View>
    _View *object_manager<_Object, _View>::get_view()
    {
        if (view == nullptr)
            view = std::shared_ptr<_View>(new_view());

        return view.get();
    }

      template<typename _Object, typename _View>
    void object_manager<_Object, _View>::on_draw(_Object *obj)
    {}

    template class object_manager<glass_pane, glass_pane_view>;
    template class object_manager<light_box, light_box_view>;
    template class object_manager<wall_obstacle, wall_obstacle_view>;
}
