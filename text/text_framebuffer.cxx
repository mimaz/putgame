/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/res>

#include "text_framebuffer.hxx"

#include "text_buffer.hxx"

namespace
{
    const float mesh[] = {
        -0.5f, 0.5f,
        0.5f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f,
    };
}

namespace text
{
    text_framebuffer::text_framebuffer(common::context *ctx)
        : part(ctx)
        , vsh(GL_VERTEX_SHADER,
              version_glsl,
              textured_rect_vsh)
        , fsh(GL_FRAGMENT_SHADER,
              version_glsl,
              text_buffer_fsh)
        , pro(&vsh, &fsh)
        , a_coord(&pro, "a_coord")
        , u_matrix(&pro, "u_matrix")
    {
        glGenFramebuffers(1, &fbhandle);
        glBindFramebuffer(GL_FRAMEBUFFER, fbhandle);

        GLenum attachement = GL_COLOR_ATTACHMENT0;
        glDrawBuffers(1, &attachement);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        pro.use();

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glVertexAttribPointer(a_coord, 2, GL_FLOAT,
                              GL_FALSE, 
                              sizeof(float) * 2,
                              mesh);
    }

    text_framebuffer::~text_framebuffer()
    {
        glDeleteFramebuffers(1, &fbhandle);
    }

    void text_framebuffer::begin(GLuint texhandle, 
                                    text_buffer *capt)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbhandle);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
                               GL_TEXTURE_2D, 
                               texhandle, 0);

        auto stat = glCheckFramebufferStatus(GL_FRAMEBUFFER);

        if (stat != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cerr << "framebuffer error: " << stat << std::endl;
            throw new std::string("framebuffer error");
        }


        glViewport(0, 0, capt->get_width(), capt->get_height());

        pro.use();

        a_coord.enable();
    }

    void text_framebuffer::draw(const glm::mat4 &matrix)
    {
        u_matrix = matrix;

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    void text_framebuffer::end()
    {
        a_coord.disable();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
