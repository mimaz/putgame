/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/gui>
#include <putgame/glutils>
#include <putgame/res>

#include "score_counter.hxx"

namespace
{
    class view : public common::context::object
    {
    public:
        view(common::context *ctx)
            : object(ctx)
            , vsh("score_counter_vsh",
                  GL_VERTEX_SHADER,
                  version_glsl,
                  score_counter_vsh)
            , fsh("score_counter_fsh",
                  GL_FRAGMENT_SHADER,
                  version_glsl,
                  score_counter_fsh)
            , pro("score_counter", &vsh, &fsh)
            , a_coord(&pro, "a_coord")
            , u_matrix(&pro, "u_matrix")
        {

        }

        void draw(gui::score_counter *self)
        {
            pro.use();
            a_coord.enable();

            common::logd("draw counter: ", self);

            a_coord.disable();
        }

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;
        glutils::attribute a_coord;
        glutils::uniform u_matrix;
    };
}

namespace gui
{
    score_counter::score_counter(common::context *ctx)
        : rect_item(ctx)
        , current_value(0)
        , value(0)
        , text(ctx, get<surface>()->get_font_builder())
    {

    }

    void score_counter::set_value(int val)
    {
        value = val;
    }

    void score_counter::draw()
    {
        rect_item::draw();

        if (current_value != value)
        {
            if (current_value < value)
                current_value++;
            else
                current_value--;

            std::ostringstream oss;
            oss << current_value;

            text.set_text(oss.str());
        }

        get<view>()->draw(this);
    }

    void score_counter::process()
    {
        rect_item::process();
    }

    int score_counter::get_value() const
    {
        return value;
    }
}
