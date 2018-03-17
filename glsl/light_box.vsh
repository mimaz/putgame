/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

attribute lowp vec3 a_coord;
attribute lowp vec3 a_normal;
attribute lowp float a_type;

uniform highp mat4 u_mvp;
uniform highp mat4 u_model;

varying lowp float v_type;
varying mediump vec3 v_coord;
varying lowp vec3 v_normal;

void main()
{
    v_type = a_type;

    v_coord = vec3(u_model * vec4(a_coord, 1.0));
    v_normal = normalize(vec3(u_model * vec4(a_normal, 0.0)));

    gl_Position = u_mvp * vec4(a_coord, 1.0);
}
