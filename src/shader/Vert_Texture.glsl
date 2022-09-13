#version 400 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec2 tex_coords;

void main()
{
    gl_Position = Projection * View * Model * vec4(pos, 1.0);
    tex_coords = tex;
}
