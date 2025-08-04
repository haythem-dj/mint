#version 330 core

layout(location = 0) in vec3 i_position;
layout(location = 1) in vec4 i_color;

out vec4 v_color;

void main()
{
    v_color = i_color;
    gl_Position = vec4(i_position, 1.0);
}