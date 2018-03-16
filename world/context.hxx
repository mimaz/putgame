/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_context_hxx
#define __world_context_hxx

#include "context_part.hxx"

namespace world
{
    class visible_object;

    class context
    {
    public:
        context(int width, int height);

        context(const context &) = delete;
        context(context &&) = delete;

        ~context();

        void draw_frame();
        void resize_frame(int width, int height);

        void register_object(visible_object *obj);
        void unregister_object(visible_object *obj);

          template<typename _Type>
        _Type *get_part();

        int get_width() const { return width; }
        int get_height() const { return height; }

    private:
        using part_ref = std::unique_ptr<context_part>;

        std::map<std::type_index, part_ref> _m_part_map;
        std::set<visible_object *> vis_objs;

        int width;
        int height;
    };

      template<typename _Type>
    _Type *context::get_part()
    {
        static_assert(std::is_base_of<context_part, _Type>::value,
                      "each part of context must derive from context_part");


        auto index = std::type_index(typeid(_Type));

        auto it = _m_part_map.find(index);

        if (it != _m_part_map.end())
            return static_cast<_Type *>(it->second.get());


        auto part = std::make_unique<_Type>(this);
        auto raw = part.get();

        _m_part_map[index] = std::move(part);

        return raw;
    }
}

#endif
