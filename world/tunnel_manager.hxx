/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_tunnel_manager_hxx
#define __world_tunnel_manager_hxx

#include "context_part.hxx"

namespace world
{
    class tunnel_view;

    class tunnel_manager : public context_part
    {
    public:
        class frame;

        tunnel_manager(context *ctx);

        void clear();
        void draw();

        void set_width(int width);
        void set_quality(int quality);

        int get_width() const { return width; }
        int get_quality() const { return quality; }

        tunnel_view *get_view();

    private:
        std::shared_ptr<tunnel_view> view;

        int width;
        int quality;
    };
}

#endif
