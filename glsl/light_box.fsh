/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

in lowp float v_type;
in mediump vec3 v_coord;
in lowp vec3 v_normal;
in lowp vec3 v_color;

out lowp vec4 out_color;

void main()
{
    lowp vec3 color;

    if (v_type < 0.5)
    {
        color = enlight(color, white,
                        v_normal, v_coord, 
                        false, true,
                        false);

        color += v_color;
    }
    else
    {
        if (v_type < 1.5)
        {
            color = v_color;
        }
        else
        {
            color = vec3(0.5, 0.5, 0.5);
        }

        color = enlight(color, white,
                        v_normal, v_coord, 
                        true, true,
                        false);
    }

    out_color = vec4(color, 1.0);
}
