/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

attribute lowp vec3 a_coord;
attribute lowp vec3 a_normal;
attribute lowp float a_type;

uniform highp mat4 u_mvp;

varying lowp float v_type;

void main()
{
    v_type = a_type;

    gl_Position = u_mvp * vec4(a_coord, 1.0);
}
