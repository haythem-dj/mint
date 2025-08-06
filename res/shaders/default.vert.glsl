#version 330 core

layout(location = 0) in vec3 i_position;
layout(location = 1) in vec4 i_color;
layout(location = 2) in vec2 i_tex_coords;

out vec4 v_color;
out vec2 v_tex_coords;

void main()
{
    v_color = i_color;
    v_tex_coords = i_tex_coords;
    gl_Position = vec4(i_position, 1.0);
}