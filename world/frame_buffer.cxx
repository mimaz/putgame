/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/res>

#include "frame_buffer.hxx"

namespace 
{
    const char *framebuffer_strerror(GLenum en)
    {
        switch (en)
        {
#define CASE(x) case x: return #x; break;
            CASE(GL_FRAMEBUFFER_UNDEFINED)
            CASE(GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
            CASE(GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
            CASE(GL_FRAMEBUFFER_UNSUPPORTED)
            CASE(GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
            default:
                return "other";
#undef CASE
        }
    }
}

namespace world
{
    frame_buffer::frame_buffer(common::context *ctx)
        : rect_item(ctx)
        , vsh("frame_buffer",
              GL_VERTEX_SHADER,
              version_glsl,
              textured_rect_vsh)
        , fsh("frame_buffer",
              GL_FRAGMENT_SHADER,
              version_glsl,
              world_frame_fsh)
        , pro("frame_buffer",
              &vsh,
              &fsh)
        , a_coord(&pro, "a_coord")
        , u_matrix(&pro, "u_matrix")
    {
        glGenFramebuffers(1, &fbhandle);
        glBindFramebuffer(GL_FRAMEBUFFER, fbhandle);

        glGenTextures(1, &txhandle);
        glBindTexture(GL_TEXTURE_2D, txhandle);
        glTexImage2D(GL_TEXTURE_2D, 
                     0, GL_RGB, 
                     956, 1044,
                     0, GL_RGB, 
                     GL_UNSIGNED_BYTE, 
                     nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


        glGenRenderbuffers(1, &rdhandle);
        glBindRenderbuffer(GL_RENDERBUFFER, rdhandle);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 956, 1044);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rdhandle);


        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
                               GL_TEXTURE_2D, txhandle, 0);

        GLenum attachments[] = { GL_COLOR_ATTACHMENT0 };
        glDrawBuffers(sizeof(attachments) / sizeof(attachments[0]), attachments);

        auto stat = glCheckFramebufferStatus(GL_FRAMEBUFFER);

        if (stat != GL_FRAMEBUFFER_COMPLETE)
            common::loge("incomplete framebuffer: ", framebuffer_strerror(stat));
    }

    frame_buffer::~frame_buffer()
    {
        glDeleteFramebuffers(1, &fbhandle);
        glDeleteRenderbuffers(1, &rdhandle);
        glDeleteTextures(1, &txhandle);
    }

    void frame_buffer::bind()
    {
        glGetIntegerv(GL_VIEWPORT, vpdata);

        glBindFramebuffer(GL_FRAMEBUFFER, fbhandle);
        glBindRenderbuffer(GL_RENDERBUFFER, rdhandle);

        glViewport(0, 0, 956, 1044);

        glClearColor(0.0, 0.25, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void frame_buffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(vpdata[0], vpdata[1], vpdata[2], vpdata[3]);
    }

    void frame_buffer::on_surface_resize(int w, int h)
    {
        rect_item::on_surface_resize(w, h);

        resize(w, h);
    }

    void frame_buffer::draw()
    {
        rect_item::draw();

        pro.use();
        a_coord.enable();

        glDisable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glVertexAttribPointer(a_coord, 2, GL_FLOAT,
                              GL_FALSE, sizeof(float) * 2,
                              rect_item::strip_mesh);

        u_matrix = glm::translate(glm::vec3(0, 0, 0));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, txhandle);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        a_coord.disable();
    }
}
