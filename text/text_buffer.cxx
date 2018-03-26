/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/res>
#include <putgame/glutils>

#include "text_buffer.hxx"

#include "font_builder.hxx"
#include "text_framebuffer.hxx"

namespace text
{
    text_buffer::text_buffer(common::context *ctx,
                                   font_builder *builder)
        : object(ctx)
        , builder(builder)
        , text("dupa")
        , font_size(1, 1)
        , width(2)
        , height(2)
        , dirty(true)
        , resized(true)
    {
        glGenTextures(1, &texhandle);

        glBindTexture(GL_TEXTURE_2D, texhandle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                        GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                        GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                        GL_CLAMP_TO_EDGE);
    }

    text_buffer::text_buffer(common::context *ctx,
                                   font_builder *builder,
                                   const std::string &text)
        : text_buffer(ctx, builder)
    {
        set_text(text);
    }

    text_buffer::~text_buffer()
    {
        glDeleteTextures(1, &texhandle);
    }

    void text_buffer::set_text(const std::string &txt)
    {
        text = txt;
        dirty = true;
    }

    void text_buffer::set_font_size(const glm::vec2 &siz)
    {
        font_size = siz;
        dirty = true;
    }

    void text_buffer::set_width(int wid)
    {
        width = wid;
        dirty = true;
        resized = true;
    }

    void text_buffer::set_height(int hei)
    {
        height = hei;
        dirty = true;
        resized = true;
    }

    GLuint text_buffer::get_texture_handle()
    {
        if (dirty)
            render();

        return texhandle;
    }

    void text_buffer::render()
    {
        auto fb = get_part<text_framebuffer>();

        glActiveTexture(GL_TEXTURE0);
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

        auto proj = glm::ortho(-get_width() / 2.0f, get_width() / 2.0f,
                               -get_height() / 2.0f, get_height() / 2.0f);

        fb->begin(texhandle, this);


        std::stringstream ss(get_text());
        std::string line;


        auto linecnt = std::count(get_text().begin(), 
                                  get_text().end(), 
                                  '\n') + 1;

        auto ycoord = (linecnt - 1) * get_font_height() / 2.0f;
       

        while (std::getline(ss, line, '\n'))
        {
            auto xcoord = -((line.length() - 1) 
                        * get_font_width()) / 2.0f;

            for (auto c : line)
            {
                auto trvec = glm::vec3(xcoord, ycoord, 0.0f);

                auto scvec = glm::vec3(get_font_width(), 
                                       get_font_height(), 
                                       1.0f);

                auto matrix = proj;

                matrix = glm::translate(matrix, trvec);
                matrix = glm::scale(matrix, scvec);

                builder->bind_texture(c);
                fb->draw(matrix);

                xcoord += get_font_width();
            }

            ycoord -= get_font_height();
        }

        fb->end();

        dirty = false;
    }
}
