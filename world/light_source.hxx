/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_light_source_hxx
#define __world_light_source_hxx

#include <putgame/common>

namespace world
{
    class light_group;

    class light_source
    {
    public:
        light_source(common::context *ctx);
        light_source(light_group *grp);

        light_source(const light_source &) = delete;
        light_source(light_source &&) = delete;

        void detach();

        virtual ~light_source() = 0;

        virtual glm::vec3 get_light_position() = 0;
        virtual glm::vec3 get_light_color() = 0;
        virtual float get_light_range() = 0;

    private:
        light_group *grp;
    };
}

#endif
