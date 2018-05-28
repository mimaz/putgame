/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

precision lowp float;
precision lowp int;

in vec2 a_coord;

uniform highp mat4 u_matrix;

out lowp vec2 v_tex_coord;

void main()
{
    v_tex_coord = a_coord + 0.5;

    gl_Position = u_matrix * vec4(a_coord, 0.0, 1.0);
}
