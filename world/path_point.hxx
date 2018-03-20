/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_path_point_hxx
#define __world_path_point_hxx

namespace world
{
    class path_point
    {
    public:
        path_point(const glm::mat4 &matrix, int index)
            : matrix(matrix)
            , index(index) {}

        const glm::mat4 &get_matrix() const { return matrix; }
        int get_index() const { return index; }

    private:
        glm::mat4 matrix;
        int index;
    };
}

#endif
