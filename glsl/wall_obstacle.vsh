/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

in lowp vec3 a_coord;
in lowp vec3 a_normal;
in lowp vec2 a_tex_coord;
in lowp float a_mode;

uniform highp mat4 u_model;
uniform highp mat4 u_mvp;
uniform lowp vec2 u_tex_factor;

out lowp vec3 v_coord;
out lowp vec3 v_normal;
out lowp vec2 v_tex_coord;
out lowp float v_mode;

void main()
{
    lowp vec4 coord4 = vec4(a_coord, 1.0);
    lowp vec4 normal4 = vec4(a_normal, 0.0);

    v_coord = vec3(u_model * coord4);
    v_normal = vec3(u_model * normal4);
    v_tex_coord = a_tex_coord * u_tex_factor;
    v_mode = a_mode;

    gl_Position = u_mvp * coord4;
}
