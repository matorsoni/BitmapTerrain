#version 400 core

in float y;
out vec4 frag_color;

const vec3 color0 = vec3(0.2, 0.2, 0.8);
const vec3 color1 = vec3(1.0, 0.0, 0.0);
vec3 color_lerp(float t)
{
    return (1 - t) * color0 + t * color1;
}

void main()
{
    frag_color = vec4(color_lerp(y), 1.0);
}
