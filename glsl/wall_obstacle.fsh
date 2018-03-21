/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

const lowp vec3 side_color = vec3(0.3, 0.3, 0.3);

uniform sampler2D u_texture;

varying lowp vec3 v_coord;
varying lowp vec3 v_normal;
varying lowp vec2 v_tex_coord;
varying lowp float v_mode;

void main()
{
    lowp vec3 color;

    if (v_mode > 0.5)
    {
        color = vec3(texture2D(u_texture, v_tex_coord));
    }
    else
    {
        color = side_color;
    }

    lowp vec3 normal = normalize(v_normal);

    color = enlight(color, white,
                    normal, v_coord,
                    true, true,
                    false);

    gl_FragColor = vec4(color, 1.0);
}
