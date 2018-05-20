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
    class way_path : public path_line
    {
    public:
        class segment;

        using segment_ref = std::shared_ptr<segment>;
        using segment_gen = std::function<segment_ref()>;

        way_path(common::context *ctx);

        void set_generator(segment_gen gen);

        void generate_back() override;
        void reset();
        void update();

    private:
        segment_ref default_generator();

        std::shared_ptr<segment> seg;
        segment_gen generator;
    };

    class way_path::segment
    {
    public:
        segment();
        segment(float length, float angle, glm::vec3 axis);

        int count;
        float angle;
        glm::vec3 axis;
    };
}

#endif
