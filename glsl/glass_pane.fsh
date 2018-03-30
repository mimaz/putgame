/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

flat in lowp vec3 v_normal;
flat in lowp vec3 v_color;
in lowp vec3 v_coord;

uniform lowp int u_specular_mode;

out lowp vec4 out_color;

void main()
{
    lowp vec3 color;

    if (u_specular_mode != 0)
    {
        color = enlight(white,
                        v_color,
                        v_normal,
                        v_coord,
                        180.0,
                        false,
                        true,
                        true);
    }
    else
    {
        color = v_color;
    }

    out_color = vec4(color, 1.0);
}
