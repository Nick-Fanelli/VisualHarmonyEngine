#version 400 core

layout(location = 0) in vec2 position;
// layout(location = 1) in vec4 color;

out vec4 vColor;

void main() {
    vColor = vec4(1, 0, 0, 1);
    gl_Position = vec4(position, 0.0, 1.0);
}