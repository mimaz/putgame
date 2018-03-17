/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std.hxx>

#include "uniform.hxx"

#include "program.hxx"
#include "exception.hxx"

namespace glutils
{
    uniform::uniform(program *prog, const GLchar *name)
        : prog(prog), name(name), bound(false) {}

    GLuint uniform::get_handle()
    {
        if (not bound)
        {
            bound = true;

            handle = glGetUniformLocation(*prog, name);

            if (handle < 0)
                throw location_error { name };
        }

        return static_cast<GLuint>(handle);
    }

    void uniform::operator=(const GLfloat &v)
    {
        glUniform1f(get_handle(), v);
    }

    void uniform::operator=(const GLint &v)
    {
        glUniform1i(get_handle(), v);
    }

    void uniform::operator=(const glm::vec2 &v)
    {
        glUniform2fv(get_handle(), 1, glm::value_ptr(v));
    }

    void uniform::operator=(const glm::vec3 &v)
    {
        glUniform3fv(get_handle(), 1, glm::value_ptr(v));
    }

    void uniform::operator=(const glm::vec4 &v)
    {
        glUniform4fv(get_handle(), 1, glm::value_ptr(v));
    }

    void uniform::operator=(const glm::mat4 &v)
    {
        glUniformMatrix4fv(get_handle(), 1, GL_FALSE, glm::value_ptr(v));
    }
}
