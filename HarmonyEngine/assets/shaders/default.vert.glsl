#version 400 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;

// uniform mat4 cameraOffset;

out vec4 vColor;

void main() {
    vColor = vec4(1, 1, 0, 1);
    gl_Position = vec4(position, 1.0, 1.0);
}