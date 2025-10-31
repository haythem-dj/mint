#version 330 core

layout(location = 0) in vec3 i_position;
layout(location = 1) in vec2 i_tex_coords;

out vec2 v_tex_coords;

uniform mat4 u_transform;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    mat4 view = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    v_tex_coords = i_tex_coords;
    gl_Position = u_projection * u_view * u_transform * vec4(i_position, 1.0);
}