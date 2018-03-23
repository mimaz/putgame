/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_context_hxx
#define __world_context_hxx

namespace world
{
    class context
    {
    public:
        context() = default;

        context(const context &) = delete;
        context(context &&) = delete;

          template<typename _Type>
        _Type *get_part();

    private:
        using part_ref = std::unique_ptr<context_part>;

        std::map<std::type_index, part_ref> part_map;
    };

      template<typename _Type>
    _Type *context::get_part()
    {
        static_assert(std::is_base_of<context_part, _Type>::value,
                      "each part of context must derive from context_part");

        auto index = std::type_index(typeid(_Type));
        auto it = part_map.find(index);

        if (it != part_map.end())
            return static_cast<_Type *>(it->second.get());

        auto part = std::make_unique<_Type>(this);
        auto raw = part.get();

        part_map[index] = std::move(part);

        return raw;
    }
}

#endif
