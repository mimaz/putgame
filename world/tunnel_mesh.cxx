/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>

#include "tunnel_mesh.hxx"

namespace world
{
    tunnel_mesh::tunnel_mesh(int quality, float width, bool stripped)
        : quality(quality)
        , width(width)
        , gap(0)
    {
        const auto indices = quality * 2;

        /*
         * data layout
         *
         * xyz l
         *
         * xyz - coordinates
         * l   - layer
         *
         * therefore 4 bytes per vertex
         */

        auto pushvert = [this, quality, width](int i, GLfloat layer) -> void {
            auto angle = PI * 2 * i / quality;

            GLfloat x = cosf(angle) * width;
            GLfloat y = sinf(angle) * width;
            GLfloat z = 0;

            vdata.push_back(x);
            vdata.push_back(y);
            vdata.push_back(z);
            vdata.push_back(layer);
        };

        auto pushindex = [this, indices](int i) -> void {
            idata.push_back(static_cast<GLushort>(i % indices));
        };

        for (int i = 0; i < quality; i++)
        {
            pushvert(i, 0);
            pushvert(i, 1);

            pushindex(i * 2);
            pushindex((i + 1) * 2 + 1);
            pushindex(i * 2 + 1);

            if (not stripped)
            {
                pushindex(i * 2);
                pushindex((i + 1) * 2);
                pushindex((i + 1) * 2 + 1);
            }
        }
    }
}
