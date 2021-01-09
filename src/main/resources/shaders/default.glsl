// ========================================================
// VERTEX SHADER
// ========================================================

#type vertex
#version 400 core

layout(location = 0) in vec3 position;

out vec4 pass_Color;

void main() {
    pass_Color = vec4(0, 0.4, 1, 1);

    gl_Position = vec4(position, 1.0f);
}

// ========================================================
// FRAGMENT SHADER
// ========================================================

#type fragment
#version 400 core

in vec4 pass_Color;
out vec4 out_Color;

void main() {
    out_Color = pass_Color;
}