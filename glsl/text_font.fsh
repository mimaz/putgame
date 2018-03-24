/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

/*
 * const lowp int max_count = ...;
 * defined at runtime
 */

in lowp vec2 v_coord;

const lowp vec3 black = vec3(0.0, 0.0, 0.0);
const lowp vec3 white = vec3(1.0, 1.0, 1.0);

uniform lowp int u_count;
uniform lowp vec2 u_begin_v[max_count];
uniform lowp vec2 u_end_v[max_count];

uniform lowp float u_thickness;

out lowp vec4 out_color;

lowp float to_point(lowp int i)
{
    lowp vec2 point = u_begin_v[i];

    return length(point - v_coord);
}

void main()
{
    lowp vec3 color = black;

    for (int i = 0; i < u_count; i++)
    {
        lowp float dist = to_point(i);

        if (dist < u_thickness)
            color = white;
    }

    out_color = vec4(color, 1.0);
}
