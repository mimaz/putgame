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

highp vec3 light_coord(lowp int idx)
{
    return u_light_coord_v[idx];
}

lowp vec3 light_color(lowp int idx)
{
    return u_light_color_v[idx];
}

highp float light_range(lowp int idx)
{
    return u_light_range_v[idx];
}

lowp float calc_fog(lowp int idx,
                    highp float raylen, 
                    highp float viewlen)
{
    mediump float range = light_range(idx);

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

    lowp float specular_ofside = pow(
        0.025, 
        1.0 / pow(
            2.0, 
            float(specular_pow_factor)
        )
    );

    for (int i = 0; i < u_light_count; i++)
    {
        mediump vec3 ray = light_coord(i) - fragment_coord;
        mediump float raylen = length(ray);
        lowp vec3 ray_norm = ray / raylen;


        lowp vec3 color = vec3(0.0, 0.0, 0.0);

        if (with_diffuse)
        {
            lowp float diffuse_cosine = dot(normal_vector, ray_norm);

            if (with_backface || diffuse_cosine > 0.0)
            {
                color += light_color(i)
                       * material_diffuse 
                       * diffuse_cosine
                       ;
            }
        }




        if (with_specular)
        {
            /*
             * TODO
             * not sure if the vector is already normalized
             */
            mediump vec3 reflection = reflect(-ray_norm, normal_vector);

            lowp float specular_cosine = dot(reflection, view_norm);


            if (with_backface || specular_cosine > specular_ofside)
            {
                lowp float specular_coefficient = specular_cosine;

                for (lowp int i = 0; i < specular_pow_factor; i++)
                    specular_coefficient *= specular_coefficient;

                color += light_color(i) 
                       * material_specular 
                       * specular_coefficient
                       ;
            }
        }

        outcolor += color * calc_fog(i, raylen, viewlen);
    }

    return outcolor;
}
