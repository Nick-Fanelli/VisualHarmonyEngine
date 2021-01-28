#version 400 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;

uniform mat4 cameraViewProjectionMatrix;

out vec4 vColor;

void main() {
    vColor = color;
    gl_Position = cameraViewProjectionMatrix * vec4(position, 1.0, 1.0);
}