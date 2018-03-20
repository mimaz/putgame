/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_path_line_hxx
#define __world_path_line_hxx

#include "path_point.hxx"

namespace world
{
    class path_line
    {
    public:
        path_line(float gap);


        void append();

        void append(float angle, const glm::vec3 &axis);


        const path_point &get_first_point() const
        { return points.front(); }

        const path_point &get_last_point() const
        { return points.back(); }

        const std::deque<path_point> &get_points() const
        { return points; }

        const path_point &get_point(int id) const;

        float get_gap() const { return gap; }

    private:
        std::deque<path_point> points;
        float gap;
    };
}

#endif