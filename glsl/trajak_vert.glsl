/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

attribute lowp vec2 a_coord;
attribute lowp vec3 a_color;

uniform highp mat4 u_matrix;

varying lowp vec3 v_color;

void main()
{
    v_color = a_color;

    gl_Position = u_matrix * vec4(a_coord, 0.0, 1.0);
}
