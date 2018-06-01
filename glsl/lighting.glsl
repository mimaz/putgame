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

    lowp float lightfac = viewlen / range;
    lowp float viewfac = viewlen / u_view_range;

    return (1.0 - lightfac * lightfac) * (1.0 - viewfac * viewfac);
}

lowp vec3 enlight(lowp vec3 material_diffuse,
                  lowp vec3 material_specular,
                  lowp vec3 normal_vector,
                  highp vec3 fragment_coord,
                  mediump float specular_pow,
                  bool with_diffuse,
                  bool with_specular,
                  bool with_backface)
{
    lowp vec3 outcolor = vec3(0.0, 0.0, 0.0);

    for (int i = 0; i < u_light_count; i++)
    {
        highp vec3 ray = light_coord(i) - fragment_coord;
        highp vec3 view = u_camera_coord - fragment_coord;


        highp float raylen = length(ray);
        highp float viewlen = length(view);


        lowp float fog_factor = calc_fog(i, raylen, viewlen);



        if (with_diffuse)
        {
            lowp float diffuse_cosine = dot(normal_vector, ray) 
                                      / raylen;

            if (diffuse_cosine > 0.0)
            {
                lowp float factor = diffuse_cosine * fog_factor;

                outcolor += material_diffuse 
                          * light_color(i) 
                          * factor;
            }
        }




        if (with_specular)
        {
            mediump vec3 reflection = -ray 
                                    - 2.0 
                                    * normal_vector 
                                    * dot(normal_vector, -ray);

            mediump float reflen = length(reflection);


            lowp float specular_cosine = dot(reflection, view) 
                                       / (viewlen * reflen);


            if (with_backface || specular_cosine > 0.0)
            {
                lowp float specular_coefficient = pow(
                    specular_cosine, 
                    specular_pow
                );


                outcolor += light_color(i) 
                          * material_specular 
                          * specular_coefficient
                          * fog_factor
                          ;
            }
        }
    }

    return outcolor;
}
