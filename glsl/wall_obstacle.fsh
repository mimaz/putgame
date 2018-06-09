/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

/*
 * const lowp vec3 side_color = ...;
 * defined at runtime
 */

uniform sampler2D u_texture;

flat in lowp vec3 v_normal;
flat in lowp int v_use_tex;
in lowp vec3 v_coord;
in lowp vec2 v_tex_coord;

out lowp vec4 out_color;

void main()
{
    lowp vec3 color;

    if (v_use_tex != 0)
    {
        color = vec3(texture(u_texture, v_tex_coord));
    }
    else
    {
        color = side_color;
    }

    color = enlight(color, 
                    white,
                    v_normal, 
                    v_coord,
                    8,
                    true, 
                    true,
                    false);

    out_color = vec4(color, 1.0);
}
