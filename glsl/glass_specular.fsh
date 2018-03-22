/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

in lowp vec3 v_coord;
in lowp vec3 v_normal;

out lowp vec4 out_color;

void main()
{
    lowp vec3 normal = normalize(v_normal);

    lowp vec3 color = enlight(black, 
                              white, 
                              normal, 
                              v_coord,
                              120.0,
                              false, 
                              true,
                              true);

    out_color = vec4(color, 1.0);
}
