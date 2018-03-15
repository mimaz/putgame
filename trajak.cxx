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
    {
        vshader = glCreateShader(GL_VERTEX_SHADER);
        assert(vshader > 0);

        glShaderSource(vshader, 1, &vcode, nullptr);
        glCompileShader(vshader);


        GLint ok;
        glGetShaderiv(vshader, GL_COMPILE_STATUS, &ok);
        assert(ok);


        fshader = glCreateShader(GL_FRAGMENT_SHADER);
        assert(fshader > 0);

        glShaderSource(fshader, 1, &fcode, nullptr);
        glCompileShader(fshader);


        glGetShaderiv(fshader, GL_COMPILE_STATUS, &ok);
        assert(ok);



        program = glCreateProgram();
        assert(program > 0);

        glAttachShader(program, vshader);
        glAttachShader(program, fshader);
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &ok);
        assert(ok);
    }

    trajak::~trajak()
    {
        glDeleteShader(vshader);
        glDeleteShader(fshader);
        glDeleteProgram(program);
    }

    void trajak::draw()
    {
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
