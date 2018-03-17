/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

const int max_light_count = 4;

uniform highp vec3 u_camera_coord;

uniform int u_light_count;
uniform highp vec3 u_light_coord_v[max_light_count];
uniform lowp vec3 u_light_color_v[max_light_count];
uniform lowp float u_light_range_v[max_light_count];

lowp vec3 enlighted(lowp vec3 material,
                    lowp vec3 normal,
                    highp vec3 coord)
{
    lowp vec3 outcolor = vec3(0.0, 0.0, 0.0);

    for (int i = 0; i < u_light_count; i++)
    {
        highp vec3 light_coord = u_light_coord_v[i];
        lowp vec3 light_color = u_light_color_v[i];

        highp vec3 ray = light_coord - coord;
        highp vec3 view = u_camera_coord - coord;

        mediump float raylen = length(ray);
        mediump float viewlen = length(view);

        // diffuse
        mediump float diffuse_cos = dot(normal, ray) / raylen;
        lowp vec3 diffuse_color = light_color * diffuse_cos;

        outcolor += material * diffuse_color;

        // specular
        highp vec3 diff = ray - normal;
        highp vec3 ref = ray - (diff * 2.0);
        mediump float reflen = length(ref);

        mediump float specular_cos = dot(ray, ref) / (raylen * reflen);
        mediump float specular_factor = pow(specular_cos, 94.0);

        lowp vec3 specular_color = light_color * specular_factor * diffuse_cos;

        outcolor += specular_color;
    }

    return outcolor;
}
