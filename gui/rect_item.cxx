/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "rect_item.hxx"

namespace gui
{
    rect_item::rect_item(common::context *ctx)
        : object(ctx)
        , xpos(0)
        , ypos(0)
        , width(1)
        , height(1)
        , dirty_matrix(true)
    {}

    void rect_item::set_position(int x, int y)
    {
        xpos = x;
        ypos = y;
        dirty_matrix = true;
    }

    void rect_item::set_size(int w, int h)
    {
        width = w;
        height = h;
        dirty_matrix = true;
    }

    glm::mat4 rect_item::get_matrix()
    {
        if (dirty_matrix)
        {
            dirty_matrix = false;

            glm::vec3 trvec(get_xpos(), get_ypos(), 0.0f);
            glm::vec3 scvec(get_width(), get_height(), 1.0f);

            matrix = glm::mat4(1);
            matrix = glm::translate(matrix, trvec);
            matrix = glm::scale(matrix, scvec);

            on_size_changed();
        }

        return matrix;
    }

    void rect_item::on_size_changed()
    {}
}
