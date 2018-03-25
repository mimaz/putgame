/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

precision lowp float;
precision lowp int;

in vec2 v_tex_coord;

uniform vec4 u_color;
uniform vec4 u_text_color;

uniform sampler2D u_texture;

out vec4 out_color;

void main()
{
    float texv = texture2D(u_texture, v_tex_coord).r;

    const float alpha = 1.0;

    if (texv < 0.5)
        out_color = u_color;
    else
        out_color = u_text_color;
}
