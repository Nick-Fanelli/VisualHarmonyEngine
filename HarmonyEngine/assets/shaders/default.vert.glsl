#version 400 core

layout(location = 0) in vec2 position;

uniform vec4 color;
uniform mat4 cameraOffset;

out vec4 vColor;

void main() {
    vColor = color;
    gl_Position = cameraOffset * vec4(position, 1.0, 1.0);
}