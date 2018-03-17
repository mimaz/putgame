/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

uniform lowp vec3 u_color;

varying lowp float v_type;
varying mediump vec3 v_coord;
varying lowp vec3 v_normal;

void main()
{
    lowp vec3 color;

    lowp float fac = dot(v_normal, -v_coord) / length(v_coord);

    if (v_type < 0.5)
        color = u_color;
    else if (v_type < 1.5)
        color = u_color * 0.5 * fac;
    else
        color = vec3(0.2, 0.2, 0.2) * fac;

    gl_FragColor = vec4(color, 1.0);
}
