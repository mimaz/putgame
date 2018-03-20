/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_pathway_hxx
#define __world_pathway_hxx

#include "context_part.hxx"

namespace world
{
    class pathway : public context_part
    {
    public:
        class point;

        static constexpr float step = 1;

        pathway(context *ctx);

        void append(float angle, const glm::vec3 &axis);

        const point &get_last() const { return points.back(); }
        const point &get_by_id(int id) const;

    private:
        std::deque<point> points;
    };

    class pathway::point
    {
    public:
        point(glm::mat4 &&matrix, int index);

        const glm::mat4 &get_matrix() const { return matrix; }
        int get_index() const { return index; }

    private:
        glm::mat4 matrix;
        int index;
    };
}

#endif
