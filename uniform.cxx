/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std.hxx>

#include "uniform.hxx"

#include "program.hxx"

namespace glutils
{
    uniform::uniform(program *prog, const GLchar *name)
        : prog(prog), name(name), handle(-1) {}

    void uniform::detach()
    {
        handle = -1;
    }

    GLuint uniform::get_handle()
    {
        if (handle < 0)
            handle = glGetUniformLocation(*prog, name);

        return handle;
    }

    void uniform::operator=(const glm::mat4 &v)
    {
        glUniformMatrix4fv(get_handle(), 1, GL_FALSE, glm::value_ptr(v));
    }
}
