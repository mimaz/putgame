/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __common_log_hxx
#define __common_log_hxx

namespace common
{
    struct __logger
    {
        using writer = void (*)(const std::ostringstream &);

        inline __logger(writer wr) : wr(wr) {}

          template<typename ..._Args>
        inline void operator()(const _Args &...args)
        {
            std::ostringstream os;
            __build_log_message(os, args...);
            wr(os);
        }

          template<typename _Arg, typename ..._Rest>
        static inline void __build_log_message(std::ostringstream &os,
                                               const _Arg &arg, 
                                               const _Rest &...rest)
        {
            os << arg;
            __build_log_message(os, rest...);
        }

        static inline void __build_log_message(std::ostringstream &os)
        {}

        static void __logd(const std::ostringstream &os);
        static void __loge(const std::ostringstream &os);
        static void __logi(const std::ostringstream &os);

        writer wr;
    };

    extern __logger logd;
    extern __logger loge;
    extern __logger logi;
}

#endif
