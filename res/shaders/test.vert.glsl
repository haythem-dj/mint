#version 330 core

layout(location = 0) in vec3 i_position;
layout(location = 1) in vec2 i_tex_coords;

out vec2 v_tex_coords;

uniform vec2 u_position;

void main()
{
    v_tex_coords = i_tex_coords;
    gl_Position = vec4(i_position+u_position, 1.0);
}