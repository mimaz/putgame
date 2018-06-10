/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

const lowp int max_light_count = 4;

const lowp vec3 white = vec3(1.0, 1.0, 1.0);
const lowp vec3 black = vec3(0.0, 0.0, 0.0);

uniform highp vec3 u_camera_coord;
uniform mediump float u_view_range;
uniform lowp int u_light_count;
uniform highp vec3 u_light_coord_v[max_light_count];
uniform lowp vec3 u_light_color_v[max_light_count];
uniform highp float u_light_range_v[max_light_count];

lowp vec3 enlight(lowp vec3 material_diffuse,
                  lowp vec3 normal_vector,
                  highp vec3 fragment_coord,
                  lowp int specular_pow_factor,
                  bool with_diffuse,
                  bool with_specular)
{
    lowp vec3 outcolor = vec3(0.0, 0.0, 0.0);

    mediump vec3 view = u_camera_coord - fragment_coord;
    mediump float viewlen = length(view);
    lowp vec3 view_norm = view / viewlen;


    mediump float specular_pow = pow(2.0, float(specular_pow_factor));

    lowp float specular_ofside = pow(
        0.025, 
        1.0 / specular_pow
    );

    for (int i = 0; i < u_light_count; i++)
    {
        mediump vec3 ray = fragment_coord - u_light_coord_v[i];
        mediump float raylen = length(ray);
        lowp vec3 ray_norm = ray / raylen;


        lowp float fog_factor = min(raylen / u_light_range_v[i], 1.0);
        lowp float fog = 1.0 - fog_factor * fog_factor;


        mediump vec3 reflection = reflect(ray_norm, normal_vector);

        lowp float diffuse_cosine = dot(reflection, normal_vector);
        lowp float specular_cosine = dot(reflection, view_norm);


        lowp float diffuse_factor = max(0.0, diffuse_cosine) * fog;

        outcolor += u_light_color_v[i] * material_diffuse * diffuse_factor;


        if (specular_cosine > specular_ofside)
        {
            lowp float specular_coefficient = pow(specular_cosine, specular_pow);
            lowp float specular_factor = specular_coefficient * fog;

            outcolor += u_light_color_v[i] * specular_factor;
        }
    }

    lowp float view_fog_factor = min(viewlen / u_view_range, 1.0);
    lowp float view_fog = 1.0 - view_fog_factor * view_fog_factor;

    return outcolor * view_fog;
}
