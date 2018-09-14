/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/res>

#include "frame_buffer.hxx"

namespace 
{
    constexpr float scale_up_factor = 1.05f;
    constexpr float scale_down_factor = 1 / scale_up_factor;

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

    const float mesh[] = {
        -1, 1, 0, 1,
        1, 1, 1, 1,
        -1, -1, 0, 0,
        1, -1, 1, 0,
    };

    int scaled_resolution(int res)
    {
        return static_cast<int>(res);
    }
}

namespace world
{
    frame_buffer::frame_buffer(common::context *ctx)
        : rect_item(ctx)
        , vsh("frame_buffer",
              GL_VERTEX_SHADER,
              version_glsl,
              world_fb_vsh)
        , fsh("frame_buffer",
              GL_FRAGMENT_SHADER,
              version_glsl,
              world_fb_fsh)
        , pro("frame_buffer",
              &vsh,
              &fsh)
        , a_coord(&pro, "a_coord")
        , a_tex_coord(&pro, "a_tex_coord")
        , vbo(GL_ARRAY_BUFFER, mesh, sizeof(mesh))
        , scaling(0.5f)
        , dirty(true)
    {
        set_depth(-50);
        resize(ctx->get_width(), ctx->get_height());

        glGenFramebuffers(1, &fbhandle);
        glGenRenderbuffers(1, &rdhandle);
        glGenTextures(1, &txhandle);

        create_texture();
    }

    frame_buffer::~frame_buffer()
    {
        destroy_texture();
    }

    void frame_buffer::bind()
    {
        glGetIntegerv(GL_VIEWPORT, vpdata);

        glBindFramebuffer(GL_FRAMEBUFFER, fbhandle);
        glBindRenderbuffer(GL_RENDERBUFFER, rdhandle);

        glViewport(0, 0, fbwidth, fbheight);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        vbo.bind();
    }

    void frame_buffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(vpdata[0], vpdata[1], vpdata[2], vpdata[3]);
    }

    void frame_buffer::set_scaling(float sc)
    {
        scaling = sc;
        dirty = true;
    }

    void frame_buffer::scale_up()
    {
        set_scaling(scaling * scale_up_factor);
    }

    void frame_buffer::scale_down()
    {
        set_scaling(scaling * scale_down_factor);
    }

    void frame_buffer::on_surface_resize(int w, int h)
    {
        rect_item::on_surface_resize(w, h);

        resize(w, h);

        dirty = true;
    }

    void frame_buffer::draw()
    {
        rect_item::draw();

        if (dirty)
        {
            dirty = false;

            create_texture();
        }

        pro.use();

        a_coord.enable();
        a_tex_coord.enable();

        glDisable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, txhandle);

        vbo.bind();

        glVertexAttribPointer(a_coord, 2, GL_FLOAT,
                              GL_FALSE, sizeof(float) * 4,
                              nullptr);
        glVertexAttribPointer(a_tex_coord, 2, GL_FLOAT,
                              GL_FALSE, sizeof(float) * 4,
                              reinterpret_cast<void *>(sizeof(float) * 2));

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        a_coord.disable();
        a_tex_coord.disable();
    }

    void frame_buffer::resize(int w, int h)
    {
        rect_item::resize(w, h);

        create_texture();
    }

    void frame_buffer::create_texture()
    {
        auto filter = GL_NEAREST;

        fbwidth = get_width() * scaling;
        fbheight = get_height() * scaling;

        common::logd("create texture:", fbwidth, ":", fbheight, ":", scaling);

        glBindFramebuffer(GL_FRAMEBUFFER, fbhandle);
        glBindTexture(GL_TEXTURE_2D, txhandle);
        glBindRenderbuffer(GL_RENDERBUFFER, rdhandle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rdhandle);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
                               GL_TEXTURE_2D, txhandle, 0);

        GLenum attachment = GL_COLOR_ATTACHMENT0;
        glDrawBuffers(1, &attachment);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, fbwidth, fbheight);
        glTexImage2D(GL_TEXTURE_2D, 
                     0, GL_RGB, 
                     fbwidth, fbheight,
                     0, GL_RGB, 
                     GL_UNSIGNED_BYTE, 
                     nullptr);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        auto stat = glCheckFramebufferStatus(GL_FRAMEBUFFER);

        if (stat != GL_FRAMEBUFFER_COMPLETE)
            common::loge("incomplete framebuffer: ", framebuffer_strerror(stat));
    }

    void frame_buffer::destroy_texture()
    {
        glDeleteFramebuffers(1, &fbhandle);
        glDeleteRenderbuffers(1, &rdhandle);
        glDeleteTextures(1, &txhandle);
    }
}
