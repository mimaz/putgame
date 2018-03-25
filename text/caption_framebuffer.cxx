/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/res>

#include "caption_framebuffer.hxx"

#include "buffered_caption.hxx"

namespace
{
    const float mesh[] = {
        -1, 1, 0, 1,
        1, 1, 1, 1,
        -1, -1, 0, 0,
        1, -1, 1, 0,
    };
}

namespace text
{
    caption_framebuffer::caption_framebuffer(common::context *ctx)
        : part(ctx)
        , vsh(GL_VERTEX_SHADER,
              version_glsl,
              caption_vsh)
        , fsh(GL_FRAGMENT_SHADER,
              version_glsl,
              caption_fsh)
        , pro(&vsh, &fsh)
        , a_coord(&pro, "a_coord")
        , u_color(&pro, "u_color")
        , u_text_color(&pro, "u_text_color")
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
                              sizeof(float) * 4,
                              mesh);
    }

    caption_framebuffer::~caption_framebuffer()
    {
        glDeleteFramebuffers(1, &fbhandle);
    }

    void caption_framebuffer::begin(GLuint texhandle, buffered_caption *capt)
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

        pro.use();
        a_coord.enable();

        u_color = capt->get_color();
        u_text_color = capt->get_text_color();
    }

    void caption_framebuffer::draw()
    {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    void caption_framebuffer::end()
    {
        a_coord.disable();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
