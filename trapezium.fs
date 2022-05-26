#version 430 core

in vec2 outPos;

out vec4 FragColor;

layout (location = 2) uniform vec2 params;

void main()
{
    if ((outPos.y >= outPos.x * params[0] + params[1]) &&
        (outPos.y >= -(outPos.x * params[0]) + params[1])) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        FragColor = vec4(1.0, 1.0, 1.0, 0.0);
    }
}
