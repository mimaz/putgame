/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */


#include "log.hxx"

#ifdef PLATFORM_ANDROID
#include <android/log.h>
#endif

namespace common
{
    namespace 
    {
        enum class level
        {
            debug,
            error,
            info
        };

        void log(level, const std::string &);

#if defined PLATFORM_GLFW
        void log(level lv, const std::string &str)
        {
            switch (lv)
            {
            case level::debug:
                std::cout << "D :: " << str << std::endl;
                break;

            case level::error:
                std::cerr << "E :: " << str << std::endl;
                break;

            case level::info:
                std::cout << "I :: " << str << std::endl;
                break;
            }
        }
#elif defined PLATFORM_ANDROID
        void log(level lv, const std::string &str)
        {
            auto tag = "putgame";
            auto cstr = str.c_str();

            switch (lv)
            {
            case level::debug:
                __android_log_print(ANDROID_LOG_DEBUG, tag, cstr);
                break;

            case level::error:
                __android_log_print(ANDROID_LOG_ERROR, tag, cstr);
                break;

            case level::info:
                __android_log_print(ANDROID_LOG_INFO, tag, cstr);
                break;
            }
        }
#else
        void log(level, const std::string &) {}
#error unknown platform
#endif
    }

    logger::logger(writer wr) : wr(wr) {}

    void logger::build_message(std::ostringstream &) {}

    logger logd(std::bind(log, level::debug, std::placeholders::_1));
    logger loge(std::bind(log, level::error, std::placeholders::_1));
    logger logi(std::bind(log, level::info, std::placeholders::_1));
}
