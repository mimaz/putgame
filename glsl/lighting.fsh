/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

precision mediump float;

const int max_light_count = 4;

const lowp vec3 white = vec3(1.0, 1.0, 1.0);
const lowp vec3 black = vec3(0.0, 0.0, 0.0);

uniform vec3 u_camera_coord;
uniform int u_light_count;
uniform vec3 u_light_coord_v[max_light_count];
uniform lowp vec3 u_light_color_v[max_light_count];
uniform float u_light_range_v[max_light_count];

vec3 light_coord(lowp int idx)
{
    return u_light_coord_v[idx];
}

lowp vec3 light_color(lowp int idx)
{
    return u_light_color_v[idx];
}

float light_range(lowp int idx)
{
    return u_light_range_v[idx];
}

lowp float calc_fog(lowp int idx,
                    float raylen, 
                    float viewlen)
{
    float div = (raylen * raylen + viewlen * viewlen) /
        light_range(idx);

    return 1.0 / (1.0 + div);
}

lowp vec3 enlight(lowp vec3 material_diffuse,
                  lowp vec3 material_specular,
                  lowp vec3 normal_vector,
                  vec3 fragment_coord,
                  float specular_pow,
                  bool with_diffuse,
                  bool with_specular,
                  bool with_backface)
{
    lowp vec3 outcolor = vec3(0.0, 0.0, 0.0);

    for (int i = 0; i < u_light_count; i++)
    {
        vec3 ray = light_coord(i) - fragment_coord;
        vec3 view = u_camera_coord - fragment_coord;


        float raylen = length(ray);
        float viewlen = length(view);


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
            vec3 reflection = -ray 
                            - 2.0 
                            * normal_vector 
                            * dot(normal_vector, -ray);

            float reflen = length(reflection);


            lowp float specular_cosine = dot(reflection, view) 
                                       / (viewlen * reflen);


            if (specular_cosine < 0.0)
                continue;

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

    return outcolor;
}
