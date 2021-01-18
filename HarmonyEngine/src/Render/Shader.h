#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLUT/glut.h>

#include <string>
#include "../Core/Utils.h"

class Shader {

    GLuint m_ProgramID, m_VertexID, m_FragmentID;

    void AttachVertexShader(const std::string& source);
    void AttachFragmentShader(const std::string& source);
    void Link();

public:
    Shader(const char* vertexFilePath, const char* fragmentFilePath)
        : m_ProgramID(glCreateProgram()) {
        AttachVertexShader(FileUtils::ReadFile(vertexFilePath));
        AttachFragmentShader(FileUtils::ReadFile(fragmentFilePath));
        Link();
    }

    void Bind();
    void Unbind();
    void Dispose();

    static const Shader& GetDefaultMeshShader() {
        static Shader defaultShader("HarmonyEngine/assets/shaders/mesh.vert.glsl", "HarmonyEngine/assets/shaders/mesh.frag.glsl");
        return defaultShader;
    }
};