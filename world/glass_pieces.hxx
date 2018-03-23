/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_glass_pieces_hxx
#define __world_glass_pieces_hxx

#include "visible_object.hxx"

namespace world
{
    class glass_pane;

    class glass_pieces : public visible_object
    {
    public:
        glass_pieces(const glass_pane *pane);
        ~glass_pieces();

        int get_count() const;

        const glm::mat4 *get_matrices() const;

    private:
        glm::vec3 color;
        std::vector<glm::mat4> matrices;
    };
}

#endif
