in lowp vec2 v_tex_coord;

uniform sampler2D u_texture;

out lowp vec4 out_color;

void main()
{
    out_color = texture2D(u_texture, v_tex_coord);
}
