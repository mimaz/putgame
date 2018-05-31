/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __common_log_hxx
#define __common_log_hxx

namespace common
{
    class logger
    {
    public:
        using writer = std::function<void(const std::string &)>;

        logger(writer);

          template<typename ..._Args>
        inline void operator()(const _Args &...args)
        {
            std::ostringstream os;
            build_message(os, args...);
            wr(os.str());
        }

    private:
          template<typename _Arg, typename ..._Rest>
        static inline void build_message(std::ostringstream &os,
                                         const _Arg &arg, 
                                         const _Rest &...rest)
        {
            os << arg;
            build_message(os, rest...);
        }

        static void build_message(std::ostringstream &os);

        writer wr;
    };

    extern logger logd;
    extern logger loge;
    extern logger logi;
}

#endif
