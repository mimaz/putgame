/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_path_line_hxx
#define __world_path_line_hxx

#include <putgame/common>

#include "path_point.hxx"

namespace world
{
    class path_line : public common::context::object
    {
    public:
        path_line(common::context *ctx, float gap);

        void append(float angle, glm::vec3 axis);
        void append(const glm::mat4 &mat);

        void remove_back();
        void remove_front();

        virtual void reset();
        virtual void reset(const glm::mat4 &matrix);

        const path_point &get_first_point() const;
        const path_point &get_last_point() const;
        const std::deque<path_point> &get_points() const;
        const path_point &get_point(int id) const;

        float get_gap() const { return gap; }

        int updated_id(glm::vec3 coord, int id) const;
        int updated_id(const glm::mat4 &mat, int id) const;

    private:
        glm::mat4 make_matrix(float angle, glm::vec3 axis) const;

        std::deque<path_point> points;
        float gap;
    };
}

#endif
