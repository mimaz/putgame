/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_way_path_hxx
#define __world_way_path_hxx

#include <putgame/common>

#include "path_line.hxx"

namespace world
{
    class way_path : public common::context::part, public path_line
    {
    public:
        class generator;

        using shared_generator = std::shared_ptr<generator>;


        way_path(common::context *ctx);

        void set_generator(shared_generator gen);

          template<typename _Type, typename ..._Args>
        void set_generator(const _Args &...args);

        void generate();

    private:
        shared_generator gen;
    };

    class way_path::generator
    {
    public:
        virtual ~generator() {}

        virtual std::pair<float, glm::vec3> generate() = 0;
    };

      template<typename _Type, typename ..._Args>
    void way_path::set_generator(const _Args &...args)
    {
        auto gen = std::make_shared<_Type>(args...);

        set_generator(gen);
    }
}

#endif
