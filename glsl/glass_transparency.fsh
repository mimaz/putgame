/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

const lowp float alpha = 0.25;

uniform lowp vec3 u_color;

in lowp vec3 v_coord;
in lowp vec3 v_normal;

out lowp vec4 out_color;

void main()
{
    out_color = vec4(u_color, alpha);
}
