/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

/*
 * const lowp int max_count;
 * defined at runtime
 */

in lowp vec2 a_coord;

uniform highp mat4 u_model_v[max_count];
uniform highp mat4 u_mvp_v[max_count];
uniform lowp vec3 u_color_v[max_count];

flat out lowp vec3 v_normal;
flat out lowp vec3 v_color;
out lowp vec3 v_coord;

void main()
{
    highp mat4 model = u_model_v[gl_InstanceID];
    highp mat4 mvp = u_mvp_v[gl_InstanceID];
    lowp vec3 color = u_color_v[gl_InstanceID];

    lowp vec4 coord4 = vec4(a_coord, 0.0, 1.0);
    lowp vec4 normal4 = vec4(0.0, 0.0, 1.0, 0.0);

    v_normal = normalize(vec3(model * normal4));
    v_color = color;
    v_coord = vec3(model * coord4);

    gl_Position = mvp * coord4;
}
