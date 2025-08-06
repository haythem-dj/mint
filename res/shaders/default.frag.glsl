#version 330 core

in vec4 v_color;
in vec2 v_tex_coords;

out vec4 o_color;

uniform vec4 u_color;
uniform sampler2D u_diffuse;

void main()
{
    o_color = v_color;
    o_color = u_color;
    o_color = texture(u_diffuse, v_tex_coords);
    // o_color = vec4(1.0, 0.0, 0.0, 1.0);
}