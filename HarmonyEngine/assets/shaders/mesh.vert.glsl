#version 400 core

layout(location = 0) in vec2 position;

uniform vec3 cameraOffset;
uniform vec4 color;

out vec4 vColor;

void main() {
    vColor = color;
    gl_Position = vec4(position + cameraOffset.xy, cameraOffset.z, 1.0);
}