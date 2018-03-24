/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/res>
#include <putgame/glutils>

#include "font_builder.hxx"

namespace
{
    constexpr auto max_count = 16;
    constexpr auto texture_width = 64;
    constexpr auto texture_height = 64;

    using character_recipe = text::font_builder::character_recipe;

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
            , u_point_count(&pro, "u_point_count")
            , u_segment_count(&pro, "u_segment_count")
            , u_point_v(&pro, "u_point_v")
            , u_segment_v(&pro, "u_segment_v")
            , u_thickness(&pro, "u_thickness")
        {
            glGenFramebuffers(1, &framebuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

            glViewport(0, 0, texture_width, texture_height);

            GLenum attachement = GL_COLOR_ATTACHMENT0;
            glDrawBuffers(1, &attachement);
        }

        ~renderer()
        {
            glDeleteFramebuffers(1, &framebuffer);
        }

        void render(GLuint texhandle,
                    const character_recipe *recipe)
        {
            std::cout << "render character: " 
                      << static_cast<int>(recipe->code) << std::endl;
            pro.use();

            a_coord.enable();

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glVertexAttribPointer(a_coord, 2, GL_FLOAT,
                                  GL_FALSE, sizeof(float) * 2,
                                  mesh);

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

            auto &points = recipe->points;
            auto &segments = recipe->segments;

            try {
                glUniform1i(u_point_count, points.size());
                glUniform2fv(u_point_v, points.size(),
                             glm::value_ptr(points.front()));

                u_thickness = 0.5f;
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
        glutils::uniform u_point_count;
        glutils::uniform u_segment_count;
        glutils::uniform u_point_v;
        glutils::uniform u_segment_v;
        glutils::uniform u_thickness;

        GLuint framebuffer;
    };
}

namespace text
{
    font_builder::font_builder(const character_recipe *recipes,
                               int recipe_count)
    {
        glGenTextures(128, textures);

        auto rdr = std::make_unique<renderer>();

        for (int i = 0; i < recipe_count; i++)
        {
            auto recipe = &recipes[i];
            auto texhandle = textures[recipe->code];

            rdr->render(texhandle, recipe);
        }
    }

    font_builder::~font_builder()
    {
        glDeleteTextures(128, textures);
    }

    void font_builder::bind_texture(int code)
    {
        glBindTexture(GL_TEXTURE_2D, textures[code]);
    }
}
