/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_tunnel_hxx
#define __world_tunnel_hxx

#include "context_part.hxx"

namespace world
{
    class tunnel_view;

    class tunnel : public context_part
    {
    public:
        class frame;

        tunnel(context *ctx);

        void draw();

        void set_width(int width);
        void set_quality(int quality);
        void set_stripped(bool stripped);

        int get_width() const { return width; }
        int get_quality() const { return quality; }
        bool is_stripped() const { return stripped; }

        tunnel_view *get_view();

    private:
        std::shared_ptr<tunnel_view> view;

        int width;
        int quality;
        bool stripped;
    };
}

#endif
