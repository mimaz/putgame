/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __common_context_hxx
#define __common_context_hxx

#define PUTGAME_OBJECT

namespace common
{
    class context
    {
    public:
        class object;

        using property_key = std::string;
        using property_value = std::variant<int>;
        using property_handler = std::function<void(const property_value &)>;
        using random_engine_type = std::default_random_engine;


        context();

        context(const context &) = delete;
        context(context &&) = delete;

        virtual ~context();

        virtual void set_property(const property_key &key, 
                                  const property_value &value);

        property_value get_property(const property_key &key) const;

        property_value get_property(const property_key &key,
                                    const property_value &def) const;

          template<typename _Type>
        _Type *get();

          template<typename _Type>
        bool is_instantied() const;

          template<typename _Type>
        void destroy();

        virtual time_t time_millis() = 0;
        virtual int get_width() = 0;
        virtual int get_height() = 0;
        virtual void exit() = 0;

        random_engine_type &get_random_engine();

    private:
        friend class object;

        using part_ref = std::unique_ptr<context::object>;

        struct handler_data
        {
            property_handler fun;
            int ident;
        };


        int register_handler(const property_key &key,
                             const property_handler &handler);
        void unregister_handler(const property_key &key,
                                int id);


        std::map<std::type_index, part_ref> part_map;
        std::map<property_key, property_value> prop_map;
        std::multimap<property_key, handler_data> handler_map;


        random_engine_type randeng;


        int hidcnt;
    };

    class context::object
    {
    protected:
        object(context *ctx);
        object(object *obj);

    public:
        using property_key = property_key;
        using property_value = property_value;

        virtual ~object();

        property_value get_property(const property_key &key) const;

        property_value get_property(const property_key &key,
                                    const property_value &def) const;

        context *get_context() const;

          template<typename _Type>
        _Type *get() const;

          template<typename _Type>
        bool is_instantied() const;

        random_engine_type &get_random_engine() const;

    protected:
        void register_handler(const property_key &key,
                              const property_handler &handler);

    private:
        using handler_data = std::pair<property_key, int>;

        context *ctx;

        std::vector<handler_data> hdatavec;
    };

      template<typename _Type>
    _Type *context::get()
    {
        auto id = std::type_index(typeid(_Type));
        auto it = part_map.find(id);

        if (it != part_map.end())
            return static_cast<_Type *>(it->second.get());

        auto uniq = std::make_unique<_Type>(this);
        auto raw = uniq.get();

        part_map[id] = std::move(uniq);

        return raw;
    }

      template<typename _Type>
    bool context::is_instantied() const
    {
        auto it = part_map.find(typeid(_Type));

        return it != part_map.end() and it->second != nullptr;
    }

      template<typename _Type>
    void context::destroy()
    {
        part_map.erase(typeid(_Type));
    }

      template<typename _Type>
    _Type *context::object::get() const
    {
        return get_context()->get<_Type>();
    }

      template<typename _Type>
    bool context::object::is_instantied() const
    {
        return get_context()->is_instantied<_Type>();
    }
}

#endif
