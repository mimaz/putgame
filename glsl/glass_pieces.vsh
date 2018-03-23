/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

/*
 * const lowp int max_extras = ...;
 * defined at runtime
 */

const lowp int max_pieces = 128;

uniform highp mat4 u_model_v[max_pieces];
uniform highp mat4 u_view_proj;
uniform lowp vec2 u_extra_v[max_extras];

flat out lowp vec3 v_normal;
out mediump vec3 v_coord;

void main()
{
    lowp vec2 coord2;

    if (gl_VertexID < 1)
        coord2 = vec2(-0.5, -0.5);
    else if (gl_VertexID < 2)
        coord2 = vec2(-0.5, 0.5);
    else 
        coord2 = u_extra_v[gl_InstanceID % max_extras];
        

    lowp vec4 coord4 = vec4(coord2, 0.0, 1.0);
    lowp vec4 normal4 = vec4(0.0, 0.0, 1.0, 0.0);

    highp mat4 model = u_model_v[gl_InstanceID];
    highp mat4 mvp = u_view_proj * model;

    v_normal = normalize(vec3(model * normal4));
    v_coord = vec3(model * coord4);

    gl_Position = mvp * coord4;
}
