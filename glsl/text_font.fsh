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

lowp float squared_distance(lowp vec2 p, lowp vec2 q)
{
    lowp vec2 d = q - p;

    return d.x * d.x + d.y * d.y;
}

lowp float segment_distance(lowp vec2 v, lowp vec2 w, lowp vec2 p)
{
    lowp float sqdist = squared_distance(w, v);

    lowp float t = dot(p - v, w - v) / sqdist;
    t = max(0.0, min(1.0, t));

    lowp vec2 proj = v + t * (w - v);

    return distance(p, proj);
}

void main()
{
    lowp vec3 color = black;

    for (int i = 0; i < u_count; i++)
    {
        if (segment_distance(u_begin_v[i], u_end_v[i], v_coord) < u_thickness)
            color = white;
    }

    out_color = vec4(color, 1.0);
}
