/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std.hxx>

#include "trajak.hxx"

namespace 
{
    const GLfloat vdata[] = {
        -0.5f, -0.5f,
        -0.5f, 0.5f,
        0.5f, -0.5f
    };

    const GLchar *vcode = R"(
    attribute lowp vec2 a_coord;

    void main()
    {
        gl_Position = vec4(a_coord, 0.0, 1.0);
    }
    )";

    const GLchar *fcode = R"(
    void main()
    {
        gl_FragColor = vec4(1.0, 0.5, 0.3, 1.0);
    }
    )";
}

namespace world
{
    trajak::trajak(context *ctx)
        : context_part(ctx)
        , vshader(GL_VERTEX_SHADER, vcode)
        , fshader(GL_FRAGMENT_SHADER, fcode)
        , program(&vshader, &fshader)
    {}

    trajak::~trajak()
    {}

    void trajak::draw()
    {
        a_coord = glGetAttribLocation(program.get_handle(), "a_coord");

        glUseProgram(program);
        glEnableVertexAttribArray(a_coord);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(a_coord, 2, GL_FLOAT, 
                              GL_FALSE, sizeof(GLfloat) * 2, 
                              vdata);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(a_coord);
    }
}
