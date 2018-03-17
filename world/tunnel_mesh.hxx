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
        tunnel_mesh(int quality);

        std::shared_ptr<GLfloat> vdata;
        GLuint vertices;
    };
}

#endif
