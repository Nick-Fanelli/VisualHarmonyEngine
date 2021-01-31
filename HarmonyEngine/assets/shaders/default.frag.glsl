#version 400 core

in vec4 vColor;
in vec2 vTextureCoord;
in float vTextureID;

out vec4 out_Color;

void main() {
    out_Color = vColor;
}