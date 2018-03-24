/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

in lowp vec2 a_coord;

out lowp vec2 v_coord;

void main()
{
    v_coord = a_coord;

    gl_Position = vec4(a_coord, 0.0, 1.0);
}
