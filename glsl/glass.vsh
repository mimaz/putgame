/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

attribute lowp vec2 a_coord;

uniform highp mat4 u_model;
uniform highp mat4 u_mvp;

varying lowp vec3 v_coord;
varying lowp vec3 v_normal;

void main()
{
    v_coord = vec3(u_model * vec4(a_coord, 0.0, 1.0));
    v_normal = vec3(u_model * vec4(0.0, 0.0, -1.0, 0.0));

    gl_Position = u_mvp * vec4(a_coord, 0.0, 1.0);
}
