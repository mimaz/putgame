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

lowp float calc_fog(lowp int idx,
                    highp float raylen, 
                    highp float viewlen)
{
    mediump float range = u_light_range_v[idx];

    lowp float lightfac = raylen / range;
    lowp float viewfac = viewlen / u_view_range;

    lowp float lightfog = (1.0 - lightfac * lightfac);
    lowp float viewfog = (1.0 - viewfac * viewfac);

    return clamp(lightfog * viewfog, 0.0, 1.0);
}

lowp vec3 enlight(lowp vec3 material_diffuse,
                  lowp vec3 material_specular,
                  lowp vec3 normal_vector,
                  highp vec3 fragment_coord,
                  lowp int specular_pow_factor,
                  bool with_diffuse,
                  bool with_specular,
                  bool with_backface)
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
        mediump vec3 ray = u_light_coord_v[i] - fragment_coord;
        mediump float raylen = length(ray);
        lowp vec3 ray_norm = ray / raylen;


        lowp vec3 color = vec3(0.0, 0.0, 0.0);

        mediump vec3 reflection = reflect(-ray_norm, normal_vector);

        lowp float diffuse_cosine = dot(normal_vector, ray_norm);
        lowp float specular_cosine = dot(reflection, view_norm);

        if (with_diffuse && (with_backface || diffuse_cosine > 0.0))
        {
            color += u_light_color_v[i]
                   * material_diffuse 
                   * diffuse_cosine
                   ;
        }

        if (with_specular && (with_backface || specular_cosine > specular_ofside))
        {
            lowp float specular_coefficient = pow(specular_cosine, specular_pow);

            color += u_light_color_v[i] 
                   * specular_coefficient
                   ;
        }

        outcolor += color * calc_fog(i, raylen, viewlen);
    }

    return outcolor;
}
