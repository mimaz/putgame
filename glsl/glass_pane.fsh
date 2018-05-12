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
    out_color = glass_color(u_specular_mode, v_color,
                            v_normal, v_coord);
}
