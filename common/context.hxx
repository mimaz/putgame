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

        context() = default;

        context(const context &) = delete;
        context(context &&) = delete;

          template<typename _Type>
        _Type *get_part();

        virtual time_t time_millis() = 0;

        std::default_random_engine &random_engine()
        { return randeng; }

    private:
        using part_ref = std::unique_ptr<context::object>;

        std::map<std::type_index, part_ref> part_map;
        std::default_random_engine randeng;
    };

    class context::object
    {
    protected:
        object(context *ctx) : ctx(ctx) {}
        object(object *obj) : object(obj->get_context()) {}

    public:
        virtual ~object() {}

        context *get_context() const { return ctx; }

          template<typename _Type>
        _Type *get_part()
        { return get_context()->get_part<_Type>(); }

        std::default_random_engine &random_engine()
        { return get_context()->random_engine(); }

    private:
        context *ctx;
    };

      template<typename _Type>
    _Type *context::get_part()
    {
        static_assert(std::is_base_of<object, _Type>::value,
                      "each part of context must derive "
                      "from context::object");

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
