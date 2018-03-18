/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

const int max_light_count = 4;

uniform mediump vec3 u_camera_coord;

uniform int u_light_count;
uniform mediump vec3 u_light_coord_v[max_light_count];
uniform lowp vec3 u_light_color_v[max_light_count];
uniform mediump float u_light_range_v[max_light_count];

lowp vec3 enlight(lowp vec3 material,
                  lowp vec3 normal,
                  mediump vec3 coord)
{
    lowp vec3 outcolor = vec3(0.0, 0.0, 0.0);

    //outcolor += material;

    for (int i = 0; i < u_light_count; i++)
    {
        mediump vec3 light_coord = u_light_coord_v[i];
        lowp vec3 light_color = u_light_color_v[i];
        mediump float light_range = u_light_range_v[i];

        mediump vec3 ray = light_coord - coord;
        mediump vec3 view = u_camera_coord - coord;

        mediump float raylen = length(ray);
        mediump float viewlen = length(view);

        lowp float fog_factor = 1.0 / (1.0 + viewlen * raylen / light_range);

        // diffuse
        lowp float diffuse_cosine = dot(normal, ray) / raylen;

        if (diffuse_cosine <= 0.0)
            continue;

        lowp float diffuse_factor = diffuse_cosine * fog_factor;

        outcolor += material * light_color * diffuse_factor;

        // specular light calculation sucks
    }

    return outcolor;
}
