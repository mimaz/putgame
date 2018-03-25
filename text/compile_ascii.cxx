/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>

#include "compile_ascii.hxx"

namespace 
{
    bool valid_symbol(char c) 
    {
        return std::isalpha(c) and std::islower(c) and c != '#';
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

            std::cout << "sym: " << *ptr << std::endl;
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
    auto ygap = 2.0f / (height - 1) - thickness / (height - 1);
    auto xgap = 2.0f / (width - 1) - thickness / (width - 1);

    auto xcoord = -1.0f + thickness / 2;
    auto ycoord = -1.0f + thickness / 2;

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

        xcoord = -1.0f + thickness / 2;
        ycoord += ygap;
    }


    ptr = ascii.get_order();


    while (*ptr == '#')
    {
        std::cout << "hash!" << std::endl;
        ptr++;

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
    }
}
