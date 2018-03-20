/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

attribute lowp vec2 a_coord;

uniform highp mat4 u_mvp;

void main()
{
    gl_Position = u_mvp * vec4(a_coord, 0.0, 1.0);
}
