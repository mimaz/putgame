/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>

#include "way_path.hxx"

namespace
{
    class default_generator : public world::way_path::generator
    {
        std::pair<float, glm::vec3> generate() override
        {
            return std::make_pair(0, glm::vec3(0, 1, 0));
        }
    };
}

namespace world
{
    way_path::way_path(common::context *ctx)
        : common::context::part(ctx)
        , path_line(1)
        , gen(std::make_shared<default_generator>())
    {}

    void way_path::set_generator(shared_generator gn)
    {
        gen = gn;
    }

    void way_path::generate()
    {
        auto [angle, axis] = gen->generate();

        append(angle, axis);
    }
}
