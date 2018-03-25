#include <putgame/std>
#include <putgame/res>

#include "test.hxx"

const float mesh[] = {
    -1, -1, 0, 0,
    -1, 1, 0, 1,
    1, 1, 1, 1,

    -1, -1, 0, 0,
    1, 1, 1, 1,
    1, -1, 1, 0,
};

test::test()
    : vsh(GL_VERTEX_SHADER,
          version_glsl,
          test_vsh)
    , fsh(GL_FRAGMENT_SHADER,
          version_glsl,
          test_fsh)
    , pro(&vsh, &fsh)
    , a_coord(&pro, "a_coord")
    , a_tex_coord(&pro, "a_tex_coord")
    , u_texture(&pro, "u_texture")
{}

void test::draw(GLuint tex)
{
    pro.use();

    a_coord.enable();
    a_tex_coord.enable();


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    u_texture = 0;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    glVertexAttribPointer(a_coord, 2, GL_FLOAT,
                          GL_FALSE, sizeof(float) * 4,
                          mesh);

    glVertexAttribPointer(a_tex_coord, 2, GL_FLOAT,
                          GL_FALSE, sizeof(float) * 4,
                          mesh + 2);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    a_coord.disable();
    a_tex_coord.disable();
}
