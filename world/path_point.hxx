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
        path_point(const glm::mat4 &matrix, int index);

        const glm::mat4 &matrix() const;
        glm::vec3 position() const;
        int index() const;

        operator glm::mat4() const;

    private:
        glm::mat4 mat;
        int idx;
    };
}

std::ostream &operator<<(std::ostream &os, const world::path_point &pt);

#endif
