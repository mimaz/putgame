/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __common_exception_hxx
#define __common_exception_hxx

namespace common
{
      template<typename _Type>
    class invalid_argument
    {
    public:
        invalid_argument(const _Type &value)
            : value(value) {}

        _Type value;
    };

      template<typename _Type>
    inline invalid_argument<_Type> make_invalid_argument(const _Type &value)
    {
        return invalid_argument<_Type>(value);
    }
}

#endif
