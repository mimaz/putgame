/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std.hxx>

#include "tunnel_mesh.hxx"

namespace world
{
    tunnel_mesh::tunnel_mesh(int quality)
    {
        const auto triangles = quality;

        vertices = triangles * 3;

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

        GLfloat *data = new GLfloat[vertices * 4];


        auto ptr = data;

        auto pushvert = [&ptr, quality](int i, GLfloat layer) -> void {
            auto angle = PI * 2 * i / quality;

            GLfloat x = cosf(angle);
            GLfloat y = sinf(angle);
            GLfloat z = 0;

            *ptr++ = x;
            *ptr++ = y;
            *ptr++ = z;
            *ptr++ = layer;
        };

        for (int i = 0; i < quality; i++)
        {
            pushvert(i + 0, 0);
            pushvert(i + 0, 1);
            pushvert(i + 1, 0);
        }

        vdata = std::shared_ptr<GLfloat>(data);
    }
}
