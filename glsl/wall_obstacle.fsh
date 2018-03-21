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
    lowp vec3 color = vec3(texture2D(u_texture, v_tex_coord));
    lowp vec3 normal = normalize(v_normal);

    color = enlight(color, white,
                    normal, v_coord,
                    true, true,
                    false);

    gl_FragColor = vec4(color, 1.0);
}
