/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __common_log_hxx
#define __common_log_hxx

namespace common
{
      template<typename _Arg, typename ..._Rest>
    inline void __build_log_message(std::ostringstream &os,
                                    const _Arg &arg, 
                                    const _Rest &...rest)
    {

    }

      template<typename ..._Args>
    inline void logd(const _Args &...args)
    {
        std::ostringstream os;
    }
}

#endif
