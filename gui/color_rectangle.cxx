/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/res>
#include <putgame/glutils>

#include "color_rectangle.hxx"

namespace 
{
    class renderer : public common::context::object
    {
    public:
        renderer(common::context *ctx)
            : object(ctx)
            , vsh("color_rectangle",
                  GL_VERTEX_SHADER,
                  version_glsl,
                  color_rectangle_vsh)
            , fsh("color_rectangle",
                  GL_FRAGMENT_SHADER,
                  version_glsl,
                  color_rectangle_fsh)
            , pro("color_rectangle", &vsh, &fsh)
            , a_coord(&pro, "a_coord")
            , u_matrix(&pro, "u_matrix")
            , u_color(&pro, "u_color")
        {}

        void draw(gui::color_rectangle *rect)
        {
            pro.use();
            a_coord.enable();

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glVertexAttribPointer(a_coord, 2, GL_FLOAT,
                                  GL_FALSE, sizeof(float) * 2,
                                  gui::rect_item::strip_mesh);

            u_matrix = rect->get_mvp();
            u_color = rect->get_color();

            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

            a_coord.disable();
        }

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;
        glutils::attribute a_coord;
        glutils::uniform u_matrix;
        glutils::uniform u_color;
    };
}

namespace gui
{
    color_rectangle::color_rectangle(common::context *ctx)
        : rect_item(ctx)
    {}

    void color_rectangle::set_color(glm::vec4 col)
    {
        color = col;
    }

    void color_rectangle::draw()
    {
        rect_item::draw();

        get<renderer>()->draw(this);
    }
}
