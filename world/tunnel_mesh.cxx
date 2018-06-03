/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/common>
#include <putgame/math>

#include "tunnel_mesh.hxx"

namespace 
{
    // determine triangle shape
    inline float triangle_height(float base)
    {
        return base * 2;
    }
}

namespace world
{
    tunnel_mesh::tunnel_mesh(int quality, float width)
        : quality(quality)
        , width(width)
        , gap(triangle_height(math::pi * width / quality))
    {
        const auto indices = quality * 2;

        /*
         * data layout
         *
         * xy - coordinates
         *
         * 2 bytes per vertex
         */

        auto pushvert = [this](float x, float y) -> void {
            vdata.push_back(x);
            vdata.push_back(y);
        };

        auto pushindex = [this, indices](int i) -> void {
            idata.push_back(static_cast<GLubyte>(i % indices));
        };

        for (int i = 0; i < quality; i++)
        {
            auto angle = math::pi * 2 * i / quality;

            GLfloat x = cosf(angle) * width / 2;
            GLfloat y = sinf(angle) * width / 2;

            pushvert(x, y);
            pushvert(x, y);

            pushindex(i * 2);
            pushindex(i * 2 + 1);
            pushindex((i + 1) * 2 + 1);

            pushindex(i * 2);
            pushindex((i + 1) * 2 + 1);
            pushindex((i + 1) * 2);
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
