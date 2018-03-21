/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

uniform sampler2D u_texture;

varying lowp vec3 v_coord;
varying lowp vec3 v_normal;
varying lowp vec2 v_tex_coord;

void main()
{
    gl_FragColor = texture2D(u_texture, v_tex_coord);
}
