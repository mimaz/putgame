/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

/*
 * const lowp int max_count = ...;
 * defined at runtime
 */

in lowp vec3 a_coord;
in lowp vec3 a_normal;
in lowp vec2 a_tex_coord;
in lowp float a_mode;

uniform highp mat4 u_model_v[max_count];
uniform highp mat4 u_mvp_v[max_count];
uniform mediump vec2 u_tex_factor_v[max_count];

flat out lowp vec3 v_normal;
flat out lowp int v_use_tex;
out lowp vec3 v_coord;
out lowp vec2 v_tex_coord;

void main()
{
    highp mat4 model = u_model_v[gl_InstanceID];
    highp mat4 mvp = u_mvp_v[gl_InstanceID];
    mediump vec2 tex_factor = u_tex_factor_v[gl_InstanceID];

    lowp vec4 coord4 = vec4(a_coord, 1.0);
    lowp vec4 normal4 = vec4(a_normal, 0.0);

    v_normal = normalize(vec3(model * normal4));
    v_use_tex = int(a_mode);
    v_coord = vec3(model * coord4);
    v_tex_coord = a_tex_coord * tex_factor;

    gl_Position = mvp * coord4;
}
