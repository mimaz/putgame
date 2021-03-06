/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/common>

#include "compile_ascii.hxx"

namespace 
{
    bool valid_symbol(char c) 
    {
        return (c >= 'a' and c <= 'z') or (c >= '0' and c <= '9');
    }

    void line(const char *&ptr,
              const std::map<int, glm::vec2> &symbolmap,
              std::vector<text::segment> &segments)
    {
        auto nextsym = [&ptr]() -> char {
            if (valid_symbol(*ptr))
                return *ptr++;

            return 0;
        };

        ptr++;

        bool strip = false;

        if (*ptr == 'S')
        {
            ptr++;
            strip = true;
        }




        char last = 0;


        while (valid_symbol(*ptr))
        {
            char sym = nextsym();

            if (last != 0)
            {
                auto bit = symbolmap.find(last);
                auto eit = symbolmap.find(sym);
                auto itend = symbolmap.end();


                if (bit == itend)
                {
                    std::cerr << "symbol " << static_cast<char>(last) 
                              << " not found" << std::endl;
                    throw std::string("error1");
                }

                if (eit == itend)
                {
                    auto excmsg = "symbol " + std::to_string(sym) +
                                  " not found";

                    throw std::string(excmsg);
                }


                auto begin = bit->second;
                auto end = eit->second;

                auto seg = std::make_pair(begin, end);


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
        }
    }

    void point(const char *&ptr,
               const std::map<int, glm::vec2> &symbolmap,
               std::vector<text::point> &points)
    {
        ptr++;
        ptr++;

        while (valid_symbol(*ptr))
        {
            auto it = symbolmap.find(*ptr++);

            if (it == symbolmap.end())
            {
                std::cerr << "symbol " << *ptr 
                          << " not found" << std::endl;

                throw std::string("error3");
            }


            auto pt = it->second;

            points.push_back(pt);
        }
    }
}

void text::compile_ascii(const ascii_character &ascii,
                         int width,
                         int height,
                         float thickness,
                         std::vector<point> &points,
                         std::vector<segment> &segments)
{
    thickness += 0.1f;

    auto ygap = 2.0f / (height - 1) - thickness * 2 / (height - 1);
    auto xgap = 2.0f / (width - 1) - thickness * 2 / (width - 1);

    auto start = -1.0f + thickness;

    auto xcoord = start;
    auto ycoord = start;

    auto ptr = ascii.get_layout();

    std::map<int, glm::vec2> symbolmap;

    for (auto y = 0; y < height; y++)
    {
        for (auto x = 0; x < width; x++)
        {
            auto c = *ptr++;

            if (valid_symbol(c))
                symbolmap[c] = glm::vec2(xcoord, -ycoord);

            xcoord += xgap;
        }

        xcoord = start;
        ycoord += ygap;
    }


    ptr = ascii.get_order();


    while (*ptr == '#')
    {
        ptr++;

        try {
            switch (*ptr)
            {
                case 'L': 
                    ::line(ptr, symbolmap, segments);
                    break;

                case 'P':
                    ::point(ptr, symbolmap, points);
                    break;

                default:
                    break;
            }
        } catch (std::string excmsg) {
            std::cerr << "compiling " 
                      << static_cast<char>(ascii.get_code())
                      << " failed: " << excmsg;

            throw excmsg;
        }
    }
}
