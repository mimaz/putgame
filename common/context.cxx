/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include "context.hxx"
#include "log.hxx"

namespace common
{
    context::context() 
        : hidcnt(100)
    {
        common::logi("created common::context");
    }

    context::~context()
    {
        common::logi("destroyed common::context");
    }

    void context::set_property(const property_key &key,
                               const property_value &value)
    {
        prop_map[key] = value;

        auto beg = handler_map.lower_bound(key);
        auto end = handler_map.upper_bound(key);

        for (auto it = beg; it != end; it++)
            it->second.fun(value);
    }

    context::property_value context::get_property(const property_key &key) const
    {
        return get_property(key, property_value());
    }

    context::property_value context::get_property(const property_key &key,
                                                  const property_value &def) const
    {
        auto it = prop_map.find(key);

        if (it != prop_map.end()) 
            return it->second;

        return def;
    }

    context::random_engine_type &context::get_random_engine()
    {
        return randeng;
    }

    int context::register_handler(const property_key &key,
                                  const property_handler &handler)
    {
        handler_data data = {
            .fun = handler,
            .ident = hidcnt,
        };  

        handler_map.insert(std::make_pair(key, data));

        handler(get_property(key));

        return hidcnt++;
    }

    void context::unregister_handler(const property_key &key,
                                     int id)
    {
        auto ran = handler_map.equal_range(key);

        auto it = std::find_if(ran.first, ran.second, 
                [id](auto entry) -> bool {
                    return entry.second.ident == id;
                });

        if (it != ran.second)
            handler_map.erase(it);
    }

    context::object::object(context *ctx)
        : ctx(ctx)
    {}

    context::object::object(object *obj)
        : object(obj->get_context())
    {}

    context::object::~object() {
        for (auto d : hdatavec)
            get_context()->unregister_handler(d.first, d.second);
    }

    context::property_value context::object::get_property(const property_key &key) const
    {
        return get_context()->get_property(key);
    }

    context::property_value context::object::get_property(const property_key &key,
                                                          const property_value &def) const
    {
        return get_context()->get_property(key, def);
    }

    context *context::object::get_context() const
    { return ctx; }

    context::random_engine_type &context::object::get_random_engine() const
    { return get_context()->get_random_engine(); }

    void context::object::register_handler(const property_key &key,
                                           const property_handler &handler)
    {
        auto id = get_context()->register_handler(key, handler);
        auto data = std::make_pair(key, id);

        hdatavec.push_back(data);
    }
}
