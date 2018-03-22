/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

/*
 * const lowp int max_count = ...;
 * are defined at runtime
 */

in lowp vec2 a_coord;

uniform highp mat4 u_model_v[max_count];
uniform highp mat4 u_mvp_v[max_count];
uniform mediump int u_hash_v[max_count];

out highp float v_blot;
out highp vec3 v_normal;
out highp vec3 v_coord;

lowp float blot(lowp int hash) 
{
    float hashf = float(hash);

    lowp vec2 arg0 = vec2(a_coord.x * hashf, a_coord.y);
    lowp vec2 arg1 = vec2(sqrt(2.0), sqrt(3.0) * hashf);

    return fract(dot(arg0, arg1) * 3.14159);
}

void main()
{
    mediump int id = gl_InstanceID + gl_VertexID % 2;

    highp mat4 model = u_model_v[id];
    highp mat4 mvp = u_mvp_v[id];
    lowp int hash = u_hash_v[id];

    lowp vec3 normal = vec3(-a_coord, 0.0);

    v_blot = blot(hash);
    v_normal = vec3(model * vec4(normal, 0.0));
    v_coord = vec3(model * vec4(a_coord, 0.0, 1.0));


    gl_Position = mvp * vec4(a_coord, 0.0, 1.0);
}
