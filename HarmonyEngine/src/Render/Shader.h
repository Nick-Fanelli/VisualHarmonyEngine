#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLUT/glut.h>

#include <string>
#include "../Core/Utils.h"

#include <glm/glm.hpp>

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
    
    void AddUniformVec4(const char* varName, const glm::vec4& vec4);
    void AddUniformVec3(const char* varName, const glm::vec3& vec3);
    void AddUniformMat4(const char* varName, const glm::mat4& mat4);
    void AddUniformInt(const char* varName, const int& integer);
    void AddUniformIntArray(const char* varName, const int& size, const int* array);

    void Bind();
    void Unbind();
    void Dispose();
};