/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/res>
#include <putgame/glutils>

#include "buffered_caption.hxx"

#include "font_builder.hxx"
#include "caption_framebuffer.hxx"

namespace text
{
    buffered_caption::buffered_caption(common::context *ctx,
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

    buffered_caption::buffered_caption(common::context *ctx,
                                   font_builder *builder,
                                   const std::string &text)
        : buffered_caption(ctx, builder)
    {
        set_text(text);
    }

    buffered_caption::~buffered_caption()
    {
        glDeleteTextures(1, &texhandle);
    }

    void buffered_caption::set_text(const std::string &txt)
    {
        text = txt;
        dirty = true;
    }
    
    void buffered_caption::set_color(const glm::vec3 &col)
    {
        color = col;
        dirty = true;
    }

    void buffered_caption::set_text_color(const glm::vec3 &col)
    {
        text_color = col;
        dirty = true;
    }

    void buffered_caption::set_width(int wid)
    {
        width = wid;
        dirty = true;
        resized = true;
    }

    void buffered_caption::set_height(int hei)
    {
        height = hei;
        dirty = true;
        resized = true;
    }

    void buffered_caption::render()
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

        auto fb = get_part<caption_framebuffer>();

        fb->begin(texhandle, this);

        glViewport(0, 0, get_width() / 2, get_height() / 2);


        glActiveTexture(GL_TEXTURE0);
        builder->bind_texture(0);


        fb->draw();
        fb->end();

        dirty = false;
        std::cout << "render!" << std::endl;
    }

    GLuint buffered_caption::get_texture_handle()
    {
        if (dirty)
            render();

        return texhandle;
    }
}
