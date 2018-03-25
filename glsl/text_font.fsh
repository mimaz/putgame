/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

/*
 * const lowp int max_count = ...;
 * defined at runtime
 */

precision lowp float;
precision lowp int;

in vec2 v_coord;

const vec3 black = vec3(0.0, 0.0, 0.0);
const vec3 white = vec3(1.0, 1.0, 1.0);

uniform int u_segment_count;
uniform vec2 u_segment_begin_v[max_count];
uniform vec2 u_segment_end_v[max_count];

uniform int u_point_count;
uniform vec2 u_point_v[max_count];

uniform float u_thickness;

out vec4 out_color;

float squared_distance(vec2 p, vec2 q)
{
    vec2 d = q - p;

    return d.x * d.x + d.y * d.y;
}

float segment_distance(vec2 v, vec2 w, vec2 p)
{
    float sqdist = squared_distance(w, v);

    float t = dot(p - v, w - v) / sqdist;
    t = max(0.0, min(1.0, t));

    vec2 proj = v + t * (w - v);

    return distance(p, proj);
}

bool covered()
{
    for (int i = 0; i < u_segment_count; i++)
    {
        if (segment_distance(u_segment_begin_v[i], 
                             u_segment_end_v[i], 
                             v_coord) < u_thickness)
        {
            return true;
        }
    }

    for (int i = 0; i < u_point_count; i++)
    {
        if (distance(u_point_v[i], v_coord) < u_thickness)
        {
            return true;
        }
    }

    return false;
}

void main()
{
    if (covered())
        out_color = vec4(1.0, 1.0, 1.0, 1.0);
    else
        out_color = vec4(0.0, 0.0, 0.0, 1.0);
}
