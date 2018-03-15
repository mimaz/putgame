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
        std::string desc;
    };

    class location_error
    {
    public:
        std::string name;
    };
}

#endif
