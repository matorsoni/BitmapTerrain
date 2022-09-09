#version 400 core

layout (location = 0) in vec3 pos;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out float y;

void main()
{
    gl_Position = Projection * View * Model * vec4(pos, 1.0);
    y = clamp(pos.y, 0.0, 1.0);
}
