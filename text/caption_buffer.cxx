/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/res>
#include <putgame/glutils>

#include "caption_buffer.hxx"

#include "font_builder.hxx"

namespace
{
    const float mesh[] = {
        -1, 1, 0, 1,
        1, 1, 1, 1,
        -1, -1, 0, 0,
        1, -1, 1, 0,
    };

    class framebuffer : public common::context::part
    {
    public:
        framebuffer(common::context *ctx)
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
            glGenFramebuffers(1, &handle);
            glBindFramebuffer(GL_FRAMEBUFFER, handle);

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

        ~framebuffer()
        {
            glDeleteFramebuffers(1, &handle);
        }

        void begin(GLuint texhandle)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, handle);


            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
                                   GL_TEXTURE_2D, texhandle, 0);

            auto stat = glCheckFramebufferStatus(GL_FRAMEBUFFER);

            if (stat != GL_FRAMEBUFFER_COMPLETE)
            {
                std::cerr << "framebuffer error: " << stat << std::endl;
                throw new std::string("framebuffer error");
            }



            pro.use();
            a_coord.enable();
        }

        void end()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            a_coord.disable();
        }

        void draw()
        {
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }

        GLuint handle;

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;
        glutils::attribute a_coord;
        glutils::uniform u_color;
        glutils::uniform u_text_color;
    };
}

namespace text
{
    caption_buffer::caption_buffer(common::context *ctx,
                                   font_builder *builder)
        : object(ctx)
        , builder(builder)
        , text("dupa")
        , color(common::red())
        , text_color(common::white())
        , width(2)
        , height(2)
        , font_size(0.1f)
        , dirty(true)
        , resized(true)
    {
        glGenTextures(1, &texhandle);

        glBindTexture(GL_TEXTURE_2D, texhandle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                        GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                        GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                        GL_CLAMP_TO_EDGE);
    }

    caption_buffer::caption_buffer(common::context *ctx,
                                   font_builder *builder,
                                   const std::string &text)
        : caption_buffer(ctx, builder)
    {
        set_text(text);
    }

    caption_buffer::~caption_buffer()
    {
        glDeleteTextures(1, &texhandle);
    }

    void caption_buffer::set_text(const std::string &txt)
    {
        text = txt;
        dirty = true;
    }
    
    void caption_buffer::set_color(const glm::vec3 &col)
    {
        color = col;
        dirty = true;
    }

    void caption_buffer::set_text_color(const glm::vec3 &col)
    {
        text_color = col;
        dirty = true;
    }

    void caption_buffer::set_width(int wid)
    {
        width = wid;
        dirty = true;
        resized = true;
    }

    void caption_buffer::set_height(int hei)
    {
        height = hei;
        dirty = true;
        resized = true;
    }

    void caption_buffer::render()
    {
        glBindTexture(GL_TEXTURE_2D, texhandle);

        if (resized)
        {
            glTexImage2D(GL_TEXTURE_2D, 
                         0, GL_RGB,
                         get_width(), get_height(),
                         0, GL_RGB,
                         GL_UNSIGNED_BYTE,
                         nullptr);

            resized = false;
        }

        auto fb = get_part<framebuffer>();

        fb->begin(texhandle);

        fb->u_color = get_color();
        fb->u_text_color = get_text_color();


        glViewport(0, 0, get_width() / 2, get_height() / 2);


        glActiveTexture(GL_TEXTURE0);
        builder->bind_texture(0);


        fb->draw();

        fb->end();

        dirty = false;
        std::cout << "render!" << std::endl;
    }

    GLuint caption_buffer::get_texture_handle()
    {
        if (dirty)
            render();

        return texhandle;
    }
}
