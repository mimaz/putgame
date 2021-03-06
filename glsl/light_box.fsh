/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

/*
 * u_type 
 * 0 - color face
 * 1 - corner
 * 2 - edge
 */

uniform lowp int u_type;

flat in lowp vec3 v_normal;
flat in lowp vec3 v_color;
in mediump vec3 v_coord;

out lowp vec4 out_color;

void main()
{
    lowp vec3 color;

    if (u_type == 0)
    {
        color = enlight(black, 
                        v_normal, 
                        v_coord, 
                        5,
                        false, 
                        true);

        color += v_color;
    }
    else
    {
        if (u_type == 1)
        {
            color = v_color;
        }
        else
        {
            color = vec3(0.5, 0.5, 0.5);
        }

        color = enlight(color, 
                        v_normal, 
                        v_coord, 
                        4,
                        true, 
                        true);
    }

    out_color = vec4(color, 1.0);
}
