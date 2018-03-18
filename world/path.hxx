/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_path_hxx
#define __world_path_hxx

#include "context_part.hxx"

namespace world
{
    class path : public context_part
    {
    public:
        class segment;

        static constexpr float step = 1;

        path(context *ctx);

        void append(float angle, const glm::vec3 &axis);

        const segment &get_last() const { return segments.back(); }
        const segment &get_by_id(int id) const;

    private:
        std::deque<segment> segments;
    };

    class path::segment
    {
    public:
        segment(glm::mat4 &&matrix, int index);

        const glm::mat4 &get_matrix() const { return matrix; }
        int get_index() const { return index; }

    private:
        glm::mat4 matrix;
        int index;
    };
}

#endif
