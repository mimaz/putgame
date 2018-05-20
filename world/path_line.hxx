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

        virtual void generate_back() = 0;

        void append(float angle, glm::vec3 axis);
        void append(const glm::mat4 &mat);
        void remove_front();
        void reset(const glm::mat4 &matrix);

        const std::deque<path_point> &points() const;
        const path_point &first_point() const;
        const path_point &last_point() const;
        const path_point &point(int id) const;

        bool empty() { return pointv.empty(); }
        float get_gap() const { return gap; }

        glm::mat4 first_matrix() const;
        glm::mat4 last_matrix() const;
        glm::mat4 matrix(int id) const;

        int first_index() const;
        int last_index() const;
        int index(int id) const;

        int updated_id(glm::vec3 coord, int id) const;
        int updated_id(const glm::mat4 &mat, int id) const;

    private:
        glm::mat4 make_matrix(float angle, glm::vec3 axis) const;

        std::deque<path_point> pointv;
        float gap;
    };
}

#endif
