/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

flat in lowp vec3 v_normal;
in mediump vec3 v_coord;

uniform lowp int u_specular_mode;
uniform lowp vec3 u_color;

out lowp vec4 out_color;

void main()
{
    out_color = glass_color(u_specular_mode, u_color,
                            v_normal, v_coord);
}
