/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/glutils>
#include <putgame/res>

#include "hit_mask.hxx"

namespace 
{
    class renderer : public common::context::object
    {
    public:
        renderer(common::context *ctx)
            : object(ctx)
            , vsh("hit_mask",
                  GL_VERTEX_SHADER,
                  version_glsl,
                  color_rectangle_vsh)
            , fsh("hit_mask",
                  GL_FRAGMENT_SHADER,
                  version_glsl,
                  color_rectangle_fsh)
            , pro("hit_mask", &vsh, &fsh)
        {}

        void draw(gui::hit_mask *mask)
        {

        }

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;

    };
}

namespace gui
{
    hit_mask::hit_mask(common::context *ctx, glm::vec4 col)
        : rect_item(ctx)
        , color(col)
        , exposure(0)
    {
        set_active(false);
    }

    void hit_mask::hit()
    {
        exposure = 1;

        set_active(true);
    }

    void hit_mask::draw()
    {
        get<renderer>()->draw(this);
    }

    void hit_mask::process()
    {
        constexpr auto speed = 0.01f;

        exposure -= speed;

        if (exposure < 0)
        {
            exposure = 0;
            set_active(false);
        }
    }

    glm::vec4 hit_mask::get_color() const
    {
        return color;
    }
}
