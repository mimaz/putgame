/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>

#include "way_path.hxx"

namespace world
{
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

    way_path::way_path(common::context *ctx)
        : common::context::part(ctx)
        , path_line(1)
    {
        for (int i = 0; i < 10; i++)
            generate_back();

        for (int i = 0; i < 10; i++)
            generate_front();
    }

    void way_path::generate_back()
    {
        if (back == nullptr or back->count < 1)
            back = generate();

        back->count--;

        append(back->angle, back->axis);
    }

    void way_path::generate_front()
    {
        if (front == nullptr or front->count < 1)
            front = generate();

        front->count--;

        prepend(front->angle, front->axis);
    }

    way_path::segment_ptr way_path::generate() const
    {
        return std::make_shared<segment>
            (10, PI / 4, glm::vec3(0, 1, 0));
    }
}
