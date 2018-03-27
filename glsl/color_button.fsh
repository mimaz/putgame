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

uniform int u_shadows;
uniform vec2 u_exposure_v[max_shadows];
uniform vec2 u_origin_v[max_shadows];
uniform sampler2D u_texture;

out vec4 out_color;

void main()
{
    out_color = vec4(0.0, 0.0, 0.0, 1.0);

    for (int i = 0; i < u_shadows; i++)
    {
        vec2 exposure = u_exposure_v[i];
        vec2 origin = u_origin_v[i];

        vec2 orgvec = v_tex_coord - origin;

        float sqexp_x = exposure.x * exposure.x;
        float sqexp_y = exposure.y * exposure.y;
        float sqdis = orgvec.x * orgvec.x + orgvec.y * orgvec.y;

        if (sqdis <= sqexp_x && sqdis >= sqexp_y)
        {
            out_color = vec4(0.75, 0.0, 0.0, 1.0);
        }
        else
        {
            out_color = vec4(0.25, 0.0, 0.0, 1.0);
        }
    }
}
