/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

const int steps = 4;

in lowp float v_blot;
in highp vec3 v_normal;
in highp vec3 v_coord;

out lowp vec4 out_color;

lowp float sharpen(lowp float val, int steps)
{
    lowp float upscaled = float(int(val * float(steps)));
    lowp float sharpened = upscaled / float(steps);

    return sharpened;
}

void main()
{
    lowp float inter = sharpen(v_blot, steps);

    lowp float v = 0.25 + inter * 0.7;

    lowp float red = v;
    lowp float green = v;
    lowp float blue = v;

    lowp vec3 color = vec3(red, green, blue);


    lowp vec3 normal = normalize(v_normal);

    color = enlight(color, 
                    normal, 
                    v_coord, 
                    8,
                    true, 
                    true);

    out_color = vec4(color, 1.0);
}
