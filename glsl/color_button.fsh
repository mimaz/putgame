/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

precision lowp float;
precision lowp int;

in vec2 v_tex_coord;

uniform sampler2D texture;

out vec4 out_color;

void main()
{
    out_color = vec4(0.1, 0.0, 0.0, 0.0);
    out_color += texture2D(texture, v_tex_coord);
}
