/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

const lowp float alpha = 0.25;

uniform lowp vec3 u_color;

in lowp vec3 v_coord;
in lowp vec3 v_normal;

void main()
{
    gl_FragColor = vec4(u_color, alpha);
}
