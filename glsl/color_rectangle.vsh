/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

in lowp vec2 a_coord;

uniform highp mat4 u_matrix;

void main()
{
    gl_Position = u_matrix * vec4(a_coord, 0.0, 1.0);
}
