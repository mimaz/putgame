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
        glass_pieces(common::context *ctx,
                     int frameid,
                     glm::vec3 color);
        glass_pieces(common::context *ctx,
                     int frameid,
                     glm::vec3 color,
                     glm::vec2 area);
        glass_pieces(common::context *ctx,
                     int frameid,
                     glm::vec3 color,
                     glm::vec2 area,
                     const glm::mat4 &transform);
        ~glass_pieces();

        void update();

        int get_count() const;
        const glm::mat4 *get_matrices() const;

        std::mutex datamtx;

    private:
        glm::vec3 color;

        std::vector<glm::mat4> matrixv;
        std::vector<int> frameidv;
    };
}

#endif
