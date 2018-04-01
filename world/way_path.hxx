/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_way_path_hxx
#define __world_way_path_hxx

#include <putgame/common>

#include "path_line.hxx"

namespace world
{
    class way_path : public common::context::part, public path_line
    {
    public:
        class segment;
        using segment_ptr = std::shared_ptr<segment>;

        way_path(common::context *ctx);

        void generate_back();
        void generate_front();

    private:
        segment_ptr generate() const;

        segment_ptr back;
        segment_ptr front;
    };
}

#endif
