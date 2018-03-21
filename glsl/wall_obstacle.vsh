/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

attribute lowp vec3 a_coord;
attribute lowp vec3 a_normal;
attribute lowp vec2 a_tex_coord;

uniform highp mat4 u_model;
uniform highp mat4 u_mvp;

varying lowp vec3 v_coord;
varying lowp vec3 v_normal;
varying lowp vec2 v_tex_coord;

void main()
{
    lowp vec4 coord4 = vec4(a_coord, 1.0);
    lowp vec4 normal4 = vec4(a_normal, 0.0);

    v_coord = vec3(u_model * coord4);
    v_normal = vec3(u_model * normal4);
    v_tex_coord = a_tex_coord;

    gl_Position = u_mvp * coord4;
}
