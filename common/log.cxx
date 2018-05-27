/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "log.hxx"

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

#ifdef PLATFORM_LINUX
        void log(level lv, const std::ostringstream &os)
        {
            auto str = os.str();

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
#endif
    }

    void __logger::__logd(const std::ostringstream &os)
    {
        log(level::debug, os);
    }

    void __logger::__loge(const std::ostringstream &os)
    {
        log(level::error, os);
    }

    void __logger::__logi(const std::ostringstream &os)
    {
        log(level::info, os);
    }

    __logger logd(__logger::__logd);
    __logger loge(__logger::__loge);
    __logger logi(__logger::__logi);
}
