#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

uniform mat4 uProjection;
uniform mat4 uView;

out vec4 pass_Color;

void main() {
    pass_Color = color;

    gl_Position = vec4(position, 1.0f);
}
