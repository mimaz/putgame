/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std.hxx>
#include <putgame-resource.h>

#include "trajak.hxx"

#include "context.hxx"
#include "camera.hxx"

namespace 
{
    const GLfloat vdata[] = {
        -0.5f, -0.5f, 1, 0, 0,
        -0.5f, 0.5f, 0, 1, 0,
        0.5f, -0.5f, 0, 0, 1,

        -0.5f, -0.5f, 1, 0, 0,
        -0.5f, 0.5f, 0, 1, 0,
        0.5f, -0.5f, 0, 0, 1,
    };
}

namespace world
{
    trajak::trajak(context *ctx)
        : context_part(ctx)
        , vshader(GL_VERTEX_SHADER, trajak_vert_glsl)
        , fshader(GL_FRAGMENT_SHADER, trajak_frag_glsl)
        , program(&vshader, &fshader)
        , a_coord(&program, "a_coord")
        , a_color(&program, "a_color")
        , u_matrix(&program, "u_matrix")
    {}

    trajak::~trajak()
    {}

    void trajak::draw()
    {
        program.use();

        a_coord.enable();
        a_color.enable();

        auto model = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
        model = glm::rotate(model, PI / 14, glm::vec3(0, 1, 0));

        u_matrix = get_context()->get_part<camera>()->get_mvp(model);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(a_coord, 2, GL_FLOAT, 
                              GL_FALSE, sizeof(GLfloat) * 5, 
                              vdata);

        glVertexAttribPointer(a_color, 3, GL_FLOAT,
                              GL_FALSE, sizeof(GLfloat) * 5,
                              vdata + sizeof(GLfloat) * 2);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        a_coord.disable();
        a_color.disable();
    }
}
