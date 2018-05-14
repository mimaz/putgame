/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/res>
#include <putgame/glutils>
#include <putgame/common>

#include "font_builder.hxx"

#include "default_font.hxx"

namespace
{
    constexpr auto max_count = 16;
    constexpr auto texture_width = 80;
    constexpr auto texture_height = 80;

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
            , u_thickness(&pro, "u_thickness")
            , u_segment_count(&pro, "u_segment_count")
            , u_segment_begin_v(&pro, "u_segment_begin_v")
            , u_segment_end_v(&pro, "u_segment_end_v")
            , u_point_count(&pro, "u_point_count")
            , u_point_v(&pro, "u_point_v")
        {
            glGenFramebuffers(1, &framebuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

            glGetIntegerv(GL_VIEWPORT, vpdata);
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
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(vpdata[0], vpdata[1], vpdata[2], vpdata[3]);
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
                            GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                            GL_LINEAR);


            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                            GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                            GL_CLAMP_TO_EDGE);


            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
                                   GL_TEXTURE_2D, texhandle, 0);

            auto stat = glCheckFramebufferStatus(GL_FRAMEBUFFER);

            if (stat != GL_FRAMEBUFFER_COMPLETE)
            {
                throw std::string("framebuffer error");
            }


            glClear(GL_COLOR_BUFFER_BIT);


            auto points = vc.get_points();
            auto segments = vc.get_segments();

            std::vector<glm::vec2> begins;
            std::vector<glm::vec2> ends;


            for (auto &seg : segments)
            {
                begins.push_back(seg.first);
                ends.push_back(seg.second);
            }

            try {
                u_thickness = vc.get_thickness();


                glUniform1i(u_segment_count, segments.size());

                glUniform2fv(u_segment_begin_v, segments.size(),
                             glm::value_ptr(begins.front()));
                glUniform2fv(u_segment_end_v, segments.size(),
                             glm::value_ptr(ends.front()));



                glUniform1i(u_point_count, points.size());

                glUniform2fv(u_point_v, points.size(),
                             glm::value_ptr(points.front()));

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
        glutils::uniform u_thickness;
        glutils::uniform u_segment_count;
        glutils::uniform u_segment_begin_v;
        glutils::uniform u_segment_end_v;
        glutils::uniform u_point_count;
        glutils::uniform u_point_v;

        GLuint framebuffer;

        int vpdata[4];
    };
}

namespace text
{
    font_builder::font_builder()
        : font_builder(default_font)
    {}

    font_builder::font_builder(const ascii_font &font)
        : textures(font.get_count())
    {
        glGenTextures(textures.size(), textures.data());


        auto rdr = std::make_unique<renderer>();


        int id = 0;


        for (auto ac : font)
        {
            auto vc = vector_character(ac, font.get_width(), 
                                       font.get_height(), 
                                       font.get_thickness());
            auto texhandle = textures[id];


            texmap[vc.get_code()] = id++;


            rdr->render(vc, texhandle);
        }
    }

    font_builder::~font_builder()
    {
        glDeleteTextures(textures.size(), textures.data());
    }

    void font_builder::bind_texture(int code)
    {
        auto idx = texmap[code];

        glBindTexture(GL_TEXTURE_2D, textures[idx]);
    }
}
