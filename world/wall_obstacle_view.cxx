/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame-std>
#include <putgame-res>

#include "wall_obstacle_view.hxx"

#include "wall_obstacle.hxx"
#include "context.hxx"
#include "camera.hxx"

namespace 
{
    const float mesh[] = {
        /*
         * data layout
         *
         * xyzghits
         *
         * xyz - coordinates
         * ghi - normal
         * ts  - texture
         *
         * 8 bytes per vertex
         */
        -0.5f, -0.5f, -0.5f, 0, 0, -1, 0, 0,
        -0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 1,
        0.5f, 0.5f, -0.5f, 0, 0, -1, 1, 1,
    };

    const float texdata[] = {
        0, 0, 0, 1, 1, 1, 
        1, 1, 1, 0, 0, 0
    };
}

namespace world
{
    wall_obstacle_view::wall_obstacle_view(context *ctx)
        : cam(ctx->get_part<camera>())
        , vsh(GL_VERTEX_SHADER, wall_obstacle_vsh)
        , fsh(GL_FRAGMENT_SHADER, 
              lighting_fsh,
              wall_obstacle_fsh)
        , pro(&vsh, &fsh)
        , a_coord(&pro, "a_coord")
        , a_normal(&pro, "a_normal")
        , a_tex_coord(&pro, "a_tex_coord")
        , u_model(&pro, "u_model")
        , u_mvp(&pro, "u_mvp")
    {
        glGenTextures(1, &texhandle);

        glBindTexture(GL_TEXTURE_2D, texhandle);

        glTexParameteri(GL_TEXTURE_2D, 
                        GL_TEXTURE_WRAP_S, 
                        GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, 
                        GL_TEXTURE_WRAP_T, 
                        GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MIN_FILTER,
                        GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MAG_FILTER,
                        GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0,
                     GL_RGB,
                     2, 2,
                     0,
                     GL_RGB,
                     GL_FLOAT,
                     texdata);
    }

    wall_obstacle_view::~wall_obstacle_view()
    {
        glDeleteTextures(1, &texhandle);
    }

    void wall_obstacle_view::begin()
    {
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);

        pro.use();

        a_coord.enable();
        a_tex_coord.enable();

        

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glVertexAttribPointer(a_coord, 3, GL_FLOAT, GL_FALSE,
                              sizeof(float) * 8,
                              mesh);

        glVertexAttribPointer(a_tex_coord, 2, GL_FLOAT, GL_FALSE,
                              sizeof(float) * 8,
                              mesh + 6);

                              
        glBindTexture(GL_TEXTURE_2D, texhandle);
    }

    void wall_obstacle_view::draw(const wall_obstacle *wall)
    {
        u_model = wall->get_model();
        u_mvp = cam->make_mvp(wall->get_model());

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void wall_obstacle_view::end()
    {
        a_coord.disable();
        a_tex_coord.disable();
    }
}
