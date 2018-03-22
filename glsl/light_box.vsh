/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

in lowp vec3 a_coord;
in lowp vec3 a_normal;
in lowp float a_type;

uniform highp mat4 u_mvp_v[2];
uniform highp mat4 u_model_v[2];
uniform lowp vec3 u_color_v[2];

out lowp float v_type;
out mediump vec3 v_coord;
out lowp vec3 v_normal;
out lowp vec3 v_color;

void main()
{
    lowp int id = gl_InstanceID;

    highp mat4 model = u_model_v[id];
    highp mat4 mvp = u_mvp_v[id];
    lowp vec3 color = u_color_v[id];

    lowp vec4 coord4 = vec4(a_coord, 1.0);
    lowp vec4 normal4 = vec4(a_normal, 0.0);

    v_type = a_type;
    v_coord = vec3(model * coord4);
    v_normal = normalize(vec3(model * normal4));
    v_color = color;

    gl_Position = mvp * coord4;
}
