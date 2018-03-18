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

    if (v_type < 0.5)
    {
        color = u_color;
    }
    else
    {
        if (v_type < 1.5)
        {
            color = u_color * 0.5;
        }
        else
        {
            color = vec3(0.25, 0.25, 0.25);
        }

        color = enlighted(color, v_normal, v_coord);
    }


    gl_FragColor = vec4(color, 1.0);
}