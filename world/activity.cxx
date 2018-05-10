/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "activity.hxx"

namespace world
{
    class activity::internal
    {
    public:
        internal(activity *act)
            : act(act)
            , alive(true)
            , preprocess_thread(std::bind(&internal::preprocess, this))
        {

        }

        ~internal()
        {
            alive = false;

            preprocess_thread.join();
        }

        void preprocess()
        {
            interval_loop(1000 / 10, []() {
                std::cout << "loop!" << std::endl;
            });
        }

    private:
        using timetype = decltype
            (static_cast<common::context *>(nullptr)->time_millis());

          template<typename _Functor>
        void interval_loop(timetype interval, _Functor functor)
        {
            auto ctx = act->get_context();
            auto next = ctx->time_millis(), curr = next;

            while (alive)
            {
                functor();
                next += interval;

                while (alive and curr < next)
                {
                    auto dur = std::chrono::microseconds(next - curr);

                    std::this_thread::sleep_for(dur);

                    curr = ctx->time_millis();
                }
            }
        }

        activity *const act;
        volatile bool alive;

        std::thread preprocess_thread;
    };

    activity::activity(common::context *ctx)
        : part(ctx)
    {}

    void activity::start()
    {
        internalptr = std::make_shared<internal>(this);
    }

    void activity::stop()
    {
        internalptr = nullptr;
    }

    bool activity::running()
    {
        return internalptr != nullptr;
    }
}
