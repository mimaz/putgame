/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/common>

#include "compile_ascii.hxx"

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

    auto valid_symbol = [](char c) -> bool {
        return std::isalpha(c) and std::islower(c);
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


    ptr = ascii.get_order();


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
