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
        , gap(PI * sqrtf(3.0f) * width / quality)
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

        auto pushvert = [this](GLfloat x, GLfloat y, 
                               GLfloat z, GLfloat l) -> void {
            vdata.push_back(x);
            vdata.push_back(y);
            vdata.push_back(z);
            vdata.push_back(l);
        };

        auto pushindex = [this, indices](int i) -> void {
            idata.push_back(static_cast<GLubyte>(i % indices));
        };

        for (int i = 0; i < quality; i++)
        {
            auto angle = PI * 2 * i / quality;

            GLfloat x = cosf(angle) * width;
            GLfloat y = sinf(angle) * width;
            GLfloat z = 0;

            pushvert(x, y, z, 0);
            pushvert(x, y, z, 1);

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

    GLuint tunnel_mesh::get_vertex_data_size() const
    {
        return vdata.size() * sizeof(GLfloat);
    }

    GLuint tunnel_mesh::get_index_count() const
    {
        return idata.size();
    }
}
