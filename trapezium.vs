#version 430 core

layout (location = 0) in vec2 aPos;

layout (location = 0) uniform mat3 model;
layout (location = 1) uniform mat3 projection;

out vec2 outPos;

void main()
{
    gl_Position = vec4(vec3(aPos / 2, 1.0) * model * projection, 1.0);
    outPos = aPos;
}
