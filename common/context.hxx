/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __common_context_hxx
#define __common_context_hxx

namespace common
{
    class context
    {
    public:
        class object;
        class part;

        context() = default;

        context(const context &) = delete;
        context(context &&) = delete;

          template<typename _Type>
        _Type *get_part();

    private:
        using part_ref = std::unique_ptr<context::part>;

        std::map<std::type_index, part_ref> part_map;
    };

    class context::object
    {
    protected:
        object(context *ctx) : ctx(ctx) {}

        virtual ~object() {}

    public:
        context *get_context() const { return ctx; }

          template<typename _Type>
        _Type *get_part()
        { return get_context()->get_part<_Type>(); }

    private:
        context *ctx;
    };

    class context::part : public object
    {
    protected:
        part(const part &) = delete;
        part(part &&) = delete;

        part(context *ctx) : object(ctx) {}

        friend class context;
    };

      template<typename _Type>
    _Type *context::get_part()
    {
        static_assert(std::is_base_of<part, _Type>::value,
                      "each part of context must derive from context::part");

        auto index = std::type_index(typeid(_Type));
        auto it = part_map.find(index);

        if (it != part_map.end())
            return static_cast<_Type *>(it->second.get());

        auto uniq = std::make_unique<_Type>(this);
        auto raw = uniq.get();

        part_map[index] = std::move(uniq);

        return raw;
    }
}

#endif
