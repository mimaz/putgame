/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_tunnel_mesh_hxx
#define __world_tunnel_mesh_hxx

namespace world
{
    class tunnel_mesh
    {
    public:
        tunnel_mesh(int quality, float width, bool stripped);

        void draw();

        const GLfloat *get_vertex_ptr() const { return vdata.data(); }
        const GLushort *get_index_ptr() const { return idata.data(); }
        GLuint get_index_count() const { return idata.size(); }

        int get_quality() const { return quality; }
        float get_gap() const { return gap; }

    private:
        std::vector<GLfloat> vdata;
        std::vector<GLushort> idata;

        int quality;
        float width;
        float gap;
    };
}

#endif