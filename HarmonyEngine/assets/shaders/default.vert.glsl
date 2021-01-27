#version 400 core

layout(location = 0) in vec2 position;

out vec4 vColor;

void main() {
    vColor = vec4(1, 1, 1, 1);
    gl_Position = vec4(position.xy, 1.0, 1.0);
}