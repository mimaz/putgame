/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __glutils_exception_hxx
#define __glutils_exception_hxx

namespace glutils
{
    class shader_error
    {
    public:
        GLenum type;
        std::string log;
        std::string code;
    };

    class location_error
    {
    public:
        explicit location_error(const std::string &tag,
                                const std::string &name);

        std::string tag;
        std::string name;
    };
}

std::ostream &operator<<(std::ostream &os, 
                         const glutils::location_error &err);

#endif
