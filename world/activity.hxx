/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_activity_hxx
#define __world_activity_hxx

#include <putgame/common>

namespace world
{
    class activity : public common::context::part
    {
    public:
        class internal;

        activity(common::context *ctx);

        void start();
        void stop();
        bool running();

    private:
        std::shared_ptr<internal> internalptr;
    };
}

#endif
