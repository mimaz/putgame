/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include "tunnel_generator.hxx"

#include "activity.hxx"

namespace game
{
    tunnel_generator::tunnel_generator(common::context *ctx)
        : object(ctx)
    {}

    world::way_path::segment_ref tunnel_generator::generate()
    {
        using segment = world::way_path::segment;

        auto dif = get<activity>()->get_difficulty();
        auto eng = get_random_engine();

        auto length = 20;
        auto max_angle = dif * 0.02f / length;

        std::uniform_real_distribution<float> angle_dist(-max_angle, max_angle);

        auto angle = angle_dist(eng);
        auto xax = angle_dist(eng);
        auto yax = angle_dist(eng);
        auto zax = 0;

        auto axis = glm::normalize(glm::vec3(xax, yax, zax));

        return std::make_shared<segment>(length, angle, axis);
    }
}
