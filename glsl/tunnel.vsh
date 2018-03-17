/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

attribute lowp vec3 a_coord;
attribute lowp float a_layer;

uniform highp mat4 u_mvp_v[2];

void main()
{
    highp mat4 mvp;

    if (a_layer < 0.5)
        mvp = u_mvp_v[0];
    else
        mvp = u_mvp_v[1];

    gl_Position = mvp * vec4(a_coord, 1.0);
}
