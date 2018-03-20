/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

const lowp float alpha = 0.5;

uniform lowp vec3 u_color;

void main()
{
    //gl_FragColor = vec4(u_color, alpha);
    gl_FragColor = vec4(1.0, 0.0, 0.0, alpha);
}
