/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

precision lowp float;
precision lowp int;

in vec2 v_tex_coord;

uniform sampler2D u_texture;

out vec4 out_color;

void main()
{
    out_color = texture2D(u_texture, v_tex_coord);
}
