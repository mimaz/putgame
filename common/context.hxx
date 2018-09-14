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

        using handler_type = std::function<void(std::string)>;
        using random_engine_type = std::default_random_engine;


        context();

        context(const context &) = delete;
        context(context &&) = delete;

        virtual ~context();

        virtual void set_property(const std::string &key, 
                                  const std::string &value);

        std::string get_property(const std::string &key) const;

        std::string get_property(const std::string &key,
                                 const std::string &def) const;

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
            handler_type fun;
            int ident;
        };


        int register_handler(const std::string &key,
                             const handler_type &handler);
        void unregister_handler(const std::string &key,
                                int id);


        std::map<std::type_index, part_ref> part_map;
        std::map<std::string, std::string> prop_map;
        std::multimap<std::string, handler_data> handler_map;


        random_engine_type randeng;


        int hidcnt;
    };

    class context::object
    {
    protected:
        object(context *ctx);
        object(object *obj);

    public:
        virtual ~object();

        std::string get_property(const std::string &key) const;

        std::string get_property(const std::string &key,
                                 const std::string &def) const;

        context *get_context() const;

          template<typename _Type>
        _Type *get() const;

          template<typename _Type>
        bool is_instantied() const;

        random_engine_type &get_random_engine() const;

    protected:
        void register_handler(const std::string &key,
                              const handler_type &handler);

    private:
        using handler_data = std::pair<std::string, int>;

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
