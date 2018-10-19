/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

in lowp vec2 v_tex_coord;

out lowp vec4 out_color;

void main()
{
    out_color = vec4(v_tex_coord, 0.0, 1.0);
}
