#version 330 core

layout(location = 0) in vec3 i_position;
layout(location = 1) in vec2 i_tex_coords;

out vec2 v_tex_coords;

uniform mat4 u_transform;

void main()
{
    v_tex_coords = i_tex_coords;
    vec4 position = u_transform * vec4(i_position, 1.0);
    gl_Position = position;
}