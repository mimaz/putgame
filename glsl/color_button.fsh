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
uniform vec4 u_primary_color;
uniform vec4 u_secondary_color;
uniform float u_ratio;
uniform int u_shadows;
uniform vec4 u_shadow_v[max_shadows];

out vec4 out_color;

bool highlighted()
{
    for (int i = 0; i < u_shadows; i++)
    {
        vec4 sh = u_shadow_v[i];

        vec2 orgvec = v_tex_coord - sh.zw;

        float sqratio = u_ratio * u_ratio;

        float sqexp_x = sh.x * sh.x;
        float sqexp_y = sh.y * sh.y;
        float sqdis = orgvec.x * orgvec.x * sqratio + orgvec.y * orgvec.y;

        if (sqdis <= sqexp_x && sqdis > sqexp_y)
            return true;
    }

    return false;
}

bool textured()
{
    return texture2D(u_texture, v_tex_coord).r > 0.5;
}

void main()
{
    if (highlighted())
    {
        if (textured())
            out_color = u_primary_color;
        else
            out_color = u_secondary_color;
    }
    else
    {
        if (textured())
            out_color = u_secondary_color;
        else
            out_color = u_primary_color;
    }
}
