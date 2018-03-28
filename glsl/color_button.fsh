/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

/*
 * const lowp int max_shadows = ...;
 * defined at runtime
 */

precision lowp float;
precision lowp int;

in vec2 v_tex_coord;

uniform sampler2D u_texture;
uniform int u_shadows;
uniform vec4 u_shadow_v[max_shadows];

out vec4 out_color;

bool highlighted()
{
    for (int i = 0; i < u_shadows; i++)
    {
        vec4 sh = u_shadow_v[i];

        vec2 orgvec = v_tex_coord - sh.zw;

        float sqexp_x = sh.x * sh.x;
        float sqexp_y = sh.y * sh.y;
        float sqdis = orgvec.x * orgvec.x + orgvec.y * orgvec.y;

        if (sqdis <= sqexp_x && sqdis > sqexp_y)
            return true;
    }

    return false;
}

void main()
{
    out_color = texture2D(u_texture, v_tex_coord);

    if (highlighted())
    {
        out_color += vec4(0.0, 0.25, 0.0, 0.0);
    }
    else
    {
        out_color += vec4(0.25, 0.0, 0.0, 0.0);
    }
}
