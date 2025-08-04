#version 330 core

in vec4 v_color;

out vec4 o_color;

uniform vec4 u_color;

void main()
{
    o_color = v_color;
    // o_color = vec4(1.0, 0.0, 0.0, 1.0);
}