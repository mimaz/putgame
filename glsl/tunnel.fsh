/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

const int steps = 4;

varying lowp float v_random;
varying highp vec3 v_normal;
varying highp vec3 v_coord;

lowp float sharpen(lowp float val, int steps)
{
    lowp float upscaled = float(int(val * float(steps)));

    lowp float sharpened = upscaled / float(steps);

    return sharpened;
}

void main()
{
    lowp float inter = sharpen(v_random, steps);

    lowp float red = 1.0;
    lowp float green = 1.0 - inter;
    lowp float blue = 1.0 - inter;

    lowp vec3 color = vec3(red, green, blue);


    lowp vec3 normal = normalize(v_normal);

    color = enlight(color, normal, v_coord);

    gl_FragColor = vec4(color, 1.0);
}
