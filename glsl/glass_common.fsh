/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

lowp vec4 glass_color(lowp int specular, lowp vec3 color,
                      lowp vec3 normal, highp vec3 coord)
{
    if (specular != 0)
    {
        color = enlight(black,
                        normal,
                        coord,
                        8,
                        false,
                        true);
    }

    return vec4(color, 1.0);
}
