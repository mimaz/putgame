/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

uniform lowp vec3 u_color;

varying lowp float v_type;

void main()
{
    lowp vec3 color;

    if (v_type < 0.5)
        color = u_color;
    else if (v_type < 1.5)
        color = u_color * 0.5;
    else
        color = vec3(0.2, 0.2, 0.2);

    gl_FragColor = vec4(color, 1.0);
}
