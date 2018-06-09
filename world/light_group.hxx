/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_light_group_hxx
#define __world_light_group_hxx

#include <putgame/common>

namespace world
{
    class light_source;

    class light_group : public common::context::object
    {
    public:
        PUTGAME_OBJECT

        light_group(common::context *ctx);
        ~light_group();

        void register_source(light_source *src);
        void unregister_source(light_source *src);

        const std::set<light_source *> get_all() const;

    private:
        std::set<light_source *> sources;
    };
}

#endif
