#version 430 core

in vec2 outPos;

out vec4 FragColor;

void main()
{
    if (outPos.x * outPos.x + outPos.y * outPos.y <= 1) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        FragColor = vec4(1.0, 1.0, 1.0, 0.0);
    }
}
