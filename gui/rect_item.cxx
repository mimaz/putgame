/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "rect_item.hxx"

#include "surface.hxx"

namespace gui
{
    rect_item::rect_item(common::context *ctx)
        : object(ctx)
        , xpos(0)
        , ypos(0)
        , width(1)
        , height(1)
        , pressed(false)
        , dirty_matrix(true)
    {
        get_part<surface>()->add_item(this);
    }

    rect_item::~rect_item()
    {
        get_part<surface>()->remove_item(this);
    }

    void rect_item::set_position(int x, int y)
    {
        xpos = x;
        ypos = y;
        dirty_matrix = true;
    }

    void rect_item::resize(int w, int h)
    {
        width = w;
        height = h;
        dirty_matrix = true;
    }

    void rect_item::draw()
    {}

    void rect_item::preprocess()
    {}

    void rect_item::touch(touch_event event)
    {
        switch (event.type)
        {
            case touch_event::press:
                pressed = true;
                break;

            case touch_event::release:
                pressed = false;
                break;

            default:
                break;
        }
    }

    void rect_item::on_surface_resize(int x, int y)
    {}

    bool rect_item::contains(int xp, int yp) const
    {
        auto l = get_xpos() - get_width() / 2;
        auto r = get_xpos() + get_width() / 2;
        auto b = get_ypos() - get_height() / 2;
        auto t = get_ypos() + get_height() / 2;

        return xp >= l and xp <= r and yp >= b and yp <= t;
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
