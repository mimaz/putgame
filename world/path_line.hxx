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
        class no_point {};

        path_line(common::context *ctx, float gap);

        void append(float angle, glm::vec3 axis);
        void append(const glm::mat4 &mat);

        void remove_back();
        void remove_front();

        virtual void reset() = 0;
        void reset_if_empty();
        void reset_matrix(const glm::mat4 &matrix);

        const path_point &first_point() const;
        const path_point &last_point() const;
        const std::deque<path_point> &points() const;
        const path_point &point(int id) const;
        bool empty() { return pointv.empty(); }

        float get_gap() const { return gap; }

        int updated_id(glm::vec3 coord, int id) const;
        int updated_id(const glm::mat4 &mat, int id) const;

    private:
        glm::mat4 make_matrix(float angle, glm::vec3 axis) const;

        std::deque<path_point> pointv;
        float gap;
    };
}

#endif
