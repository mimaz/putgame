/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

vec4 glass_color(lowp int specular, lowp vec3 color,
                 lowp vec3 normal, highp vec3 coord)
{
    if (specular != 0)
    {
        color = enlight(white,
                        white,
                        normal,
                        coord,
                        180.0,
                        false,
                        true,
                        true);
    }
    else
    {
        color *= 0.5;
    }

    return vec4(color, 1.0);
}
