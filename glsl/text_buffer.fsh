/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

in lowp vec2 v_tex_coord;

uniform sampler2D u_texture;

out lowp vec4 out_color;

void main()
{
    out_color = texture(u_texture, v_tex_coord);
}
