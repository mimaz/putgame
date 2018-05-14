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
        using segment_gen = std::function<segment_ref(void)>;

        way_path(common::context *ctx);

        void set_generator(segment_gen gen);

        void camera_moved();
        void update();

        int get_camera_frame();

    private:
        void generate_frame();
        void update_camera_frame();

        std::shared_ptr<segment> seg;
        segment_gen generator;
        int camera_frame;
        bool dirty_camera_frame;
    };

    class way_path::segment
    {
    public:
        segment()
            : segment(0, 0, glm::vec3(0, 1, 0)) {}

        segment(int count, float angle, glm::vec3 axis)
            : count(count), angle(angle / count), axis(axis) {}

        int count;
        float angle;
        glm::vec3 axis;
    };
}

#endif
