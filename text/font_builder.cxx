/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/res>
#include <putgame/glutils>
#include <putgame/common>

#include "font_builder.hxx"

namespace
{
    constexpr auto max_count = 16;
    constexpr auto texture_width = 100;
    constexpr auto texture_height = 100;

    using seg_vec = std::vector<std::pair<glm::vec2, glm::vec2>>;

    const float mesh[] = {
        -1, -1,
        -1, 1,
        1, 1,
        -1, -1,
        1, 1,
        1, -1,
    };

    class renderer
    {
    public:
        renderer()
            : vsh(GL_VERTEX_SHADER,
                  version_glsl,
                  text_font_vsh)
            , fsh(GL_FRAGMENT_SHADER,
                  version_glsl,
                  "const lowp int max_count = " + 
                  std::to_string(max_count) + ";",
                  text_font_fsh)
            , pro(&vsh, &fsh)
            , a_coord(&pro, "a_coord")
            , u_count(&pro, "u_count")
            , u_begin_v(&pro, "u_begin_v")
            , u_end_v(&pro, "u_end_v")
            , u_thickness(&pro, "u_thickness")
        {
            glGenFramebuffers(1, &framebuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

            glViewport(0, 0, texture_width, texture_height);

            GLenum attachement = GL_COLOR_ATTACHMENT0;



            pro.use();

            a_coord.enable();

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glVertexAttribPointer(a_coord, 2, GL_FLOAT,
                                  GL_FALSE, sizeof(float) * 2,
                                  mesh);

            glDrawBuffers(1, &attachement);
        }

        ~renderer()
        {
            glDeleteFramebuffers(1, &framebuffer);
        }

        void render(const text::vector_character &vc,
                    GLuint texhandle)
        {
            glBindTexture(GL_TEXTURE_2D, texhandle);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
                         texture_width, texture_height,
                         0, GL_RGB, 
                         GL_UNSIGNED_BYTE,
                         nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                            GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                            GL_NEAREST);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
                                   GL_TEXTURE_2D, texhandle, 0);

            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) !=
                    GL_FRAMEBUFFER_COMPLETE)
            {
                throw new std::string("framebuffer error");
            }


            auto segments = vc.get_segments();
            auto count = segments.size();

            std::vector<glm::vec2> begins;
            std::vector<glm::vec2> ends;


            for (auto &seg : segments)
            {
                begins.push_back(seg.first);
                ends.push_back(seg.second);
            }

            try {
                glUniform1i(u_count, count);

                glUniform2fv(u_begin_v, count,
                             glm::value_ptr(begins.front()));
                glUniform2fv(u_end_v, count,
                             glm::value_ptr(ends.front()));

                u_thickness = vc.get_thickness() / 2;
            } catch(glutils::location_error e) {
                std::cerr << "font_builder location error: " 
                          << e.name << std::endl;
            }

            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        glutils::shader vsh;
        glutils::shader fsh;
        glutils::program pro;
        glutils::attribute a_coord;
        glutils::uniform u_count;
        glutils::uniform u_begin_v;
        glutils::uniform u_end_v;
        glutils::uniform u_thickness;

        GLuint framebuffer;
    };
}

namespace text
{
    font_builder::font_builder(int count)
        : textures(new GLuint[count])
        , count(count)
    {
        glGenTextures(count, textures);
    }

    font_builder::~font_builder()
    {
        glDeleteTextures(count, textures);
    }

    void font_builder::render(const vector_character *begin, 
                              const vector_character *end)
    {
        auto rdr = std::make_unique<renderer>();

        auto ptr = begin;


        while (ptr != end)
        {
            auto vc = *ptr++;
            auto texhandle = textures[vc.get_code()];

            rdr->render(vc, texhandle);
        }
    }

    void font_builder::render(const ascii_character *begin,
                              const ascii_character *end,
                              int ascii_width,
                              int ascii_height,
                              float thickness)
    {
        std::vector<vector_character> vcs;

        for (auto ptr = begin; ptr != end; ptr++)
            vcs.emplace_back(*ptr, ascii_width, ascii_height, thickness);

        render(vcs.data(), vcs.data() + vcs.size());
    }

    void font_builder::bind_texture(int code)
    {
        glBindTexture(GL_TEXTURE_2D, textures[code]);
    }
}
