/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include "frame_buffer.hxx"

namespace world
{
    frame_buffer::frame_buffer(common::context *ctx)
        : rect_item(ctx)
    {
        glGenFramebuffers(1, &fbhandle);
        glGenRenderbuffers(1, &rdhandle);
        glGenTextures(1, &txhandle);

        glBindFramebuffer(GL_FRAMEBUFFER, fbhandle);
        glBindRenderbuffer(GL_RENDERBUFFER, rdhandle);
        glBindTexture(GL_TEXTURE_2D, txhandle);

        GLenum attachement = GL_COLOR_ATTACHMENT0;
        glDrawBuffers(1, &attachement);

        glTexImage2D(GL_TEXTURE_2D, 
                     0, GL_RGBA, 
                     100, 100, 
                     0, GL_RGBA, 
                     GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 100, 100);
        //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rdhandle);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
                               GL_TEXTURE_2D, txhandle, 0);


        auto stat = glCheckFramebufferStatus(GL_FRAMEBUFFER);

        if (stat != GL_FRAMEBUFFER_COMPLETE)
            common::loge("incomplete framebuffer!");
    }

    frame_buffer::~frame_buffer()
    {
        glDeleteFramebuffers(1, &fbhandle);
        glDeleteRenderbuffers(1, &rdhandle);
        glDeleteTextures(1, &txhandle);
    }

    void frame_buffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbhandle);
    }

    void frame_buffer::on_surface_resize(int w, int h)
    {
        rect_item::on_surface_resize(w, h);

        resize(w, h);
    }

    void frame_buffer::draw()
    {
        rect_item::draw();

        common::logd("draw!");
        // TODO draw texture
    }
}
