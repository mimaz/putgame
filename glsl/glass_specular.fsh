/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

in lowp vec3 v_coord;
in lowp vec3 v_normal;

void main()
{
    lowp vec3 normal = normalize(v_normal);

    lowp vec3 color = enlight(black, white, 
                              normal, v_coord,
                              false, true,
                              true);

    gl_FragColor = vec4(color, 1.0);
}
