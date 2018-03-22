/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

/*
 * const int blot_size is defined at runtime
 */

in lowp vec3 a_coord;
in lowp float a_layer;
in highp float a_index;

uniform highp mat4 u_model_0;
uniform highp mat4 u_model_1;

uniform highp mat4 u_mvp_0;
uniform highp mat4 u_mvp_1;

uniform lowp float u_random_0[blot_size];
uniform lowp float u_random_1[blot_size];

out highp float v_random;
out highp vec3 v_normal;
out highp vec3 v_coord;

void main()
{
    highp mat4 mvp;
    highp mat4 model;

    if (a_layer < 0.5)
    {
        mvp = u_mvp_0;
        model = u_model_0;

        v_random = u_random_0[int(a_index)];
    }
    else
    {
        mvp = u_mvp_1;
        model = u_model_1;

        v_random = u_random_1[int(a_index)];
    }


    lowp vec3 normal = vec3(-a_coord.xy, 0.0);


    v_normal = vec3(model * vec4(normal, 0.0));
    v_coord = vec3(model * vec4(a_coord, 1.0));


    gl_Position = mvp * vec4(a_coord, 1.0);
}
