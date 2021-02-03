#version 400 core

in vec4 vColor;
in vec2 vTextureCoord;
in float vTextureID;

// uniform sampler2D uTexture;

out vec4 out_Color;

void main() {
	vTextureCoord;
	vTextureID;
    out_Color = vColor;
    // out_Color = texture(uTexture, vTextureCoord);
}