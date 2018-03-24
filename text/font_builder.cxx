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

    class mapped_character
    {
    public:
        mapped_character(float thickness,
                         int width, int height, 
                         const text::font_builder::char_desc &desc)
        {
            auto ygap = 2.0f / (height - 1) - thickness / (height - 1);
            auto xgap = 2.0f / (width - 1) - thickness / (width - 1);

            auto xcoord = -1.0f + thickness / 2;
            auto ycoord = -1.0f + thickness / 2;

            auto ptr = desc.map;

            auto valid_symbol = [](char c) -> bool {
                return c > ' ';
            };

            std::map<char, glm::vec2> symbolmap;

            for (auto y = 0; y < height; y++)
            {
                for (auto x = 0; x < width; x++)
                {
                    auto c = *ptr++;

                    if (valid_symbol(c))
                        symbolmap[c] = glm::vec2(xcoord, -ycoord);

                    xcoord += xgap;
                }

                xcoord = -1.0f + thickness / 2;
                ycoord += ygap;
            }


            ptr = desc.order;


            auto nextsym = [&ptr, valid_symbol]() -> char {
                if (valid_symbol(*ptr))
                    return *ptr++;

                return 0;
            };


            while (*ptr == '#')
            {
                ptr++;

                switch (*ptr)
                {
                    case 'L': 
                    {
                        ptr++;

                        bool strip = false;

                        if (*ptr == 'S')
                        {
                            ptr++;
                            strip = true;
                        }




                        char last = 0;
                        char sym = nextsym();


                        while (sym != 0)
                        {
                            if (last != 0 && sym != 0)
                            {
                                auto bit = symbolmap.find(last);
                                auto eit = symbolmap.find(sym);
                                auto itend = symbolmap.end();


                                if (bit == itend)
                                {
                                    std::cerr << "symbol " << last 
                                              << " not found" << std::endl;
                                    throw new std::string("error1");
                                }

                                if (eit == itend)
                                {
                                    std::cerr << "symbol " << sym
                                              << " not found" << std::endl;
                                    throw new std::string("error2");
                                }


                                auto begin = bit->second;
                                auto end = eit->second;

                                auto seg = std::make_pair(begin, end);

                                std::cout << "line: " << begin << " -> "
                                          << end << std::endl;

                                segments.push_back(seg);



                                if (strip)
                                {
                                    last = sym;
                                }
                                else
                                {
                                    last = 0;
                                }
                            }
                            else
                            {
                                last = sym;
                            }

                            sym = nextsym();
                        }

                        break;
                    }

                    case 'P':
                        ptr++;
                        break;

                    default:
                        break;
                }
            }
        }

        seg_vec segments;
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
            glDrawBuffers(1, &attachement);
        }

        ~renderer()
        {
            glDeleteFramebuffers(1, &framebuffer);
        }

        void render(float thickness,
                    GLuint texhandle, 
                    const mapped_character &mchr)
        {
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


            auto segments = mchr.segments;
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

                u_thickness = thickness / 2;
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
    font_builder::font_builder(float thickness,
                               int width, int height,
                               const data_map &font_data)
    {
        glGenTextures(128, textures);

        auto rdr = std::make_unique<renderer>();

        for (auto p : font_data)
        {
            auto mchr = mapped_character(thickness, width, height, p.second);
            auto than = textures[p.first];

            rdr->render(thickness, than, mchr);
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
