#include "Shader.h"

#include <vector>
#include <string> 
#include <regex>
#include <glm/gtc/type_ptr.hpp>
#include "../Core/Log.h"

void Shader::AttachVertexShader(std::string& source) {
    if(m_Replacements != nullptr) {
        for(auto replacement : *m_Replacements) {
            std::regex regex = std::regex("\\$" + replacement.first + "\\$");
            source = std::regex_replace(source, regex, replacement.second);
        }
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    m_VertexID = glCreateShader(GL_VERTEX_SHADER);
    const char* sourcePointer = source.c_str();
    glShaderSource(m_VertexID, 1, &sourcePointer, NULL);
    glCompileShader(m_VertexID);

    // Check Compilation Status
    glGetShaderiv(m_VertexID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(m_VertexID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if(InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(m_VertexID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        Log::Error(&VertexShaderErrorMessage[0]);
    }

    Log::Info("Attaching Vertex Shader...");
    glAttachShader(m_ProgramID, m_VertexID);
    Log::Success("Attached Vertex Shader!");
}

void Shader::AttachFragmentShader(std::string& source) {
    if(m_Replacements != nullptr) {
        for(auto replacement : *m_Replacements) {
            std::regex regex = std::regex("\\$" + replacement.first + "\\$");
            source = std::regex_replace(source, regex, replacement.second);
        }
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    m_FragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* sourcePointer = source.c_str();
    glShaderSource(m_FragmentID, 1, &sourcePointer, NULL);
    glCompileShader(m_FragmentID);

    // Check Compilation Status
    glGetShaderiv(m_FragmentID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(m_FragmentID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if(InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(m_FragmentID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        Log::Error(&FragmentShaderErrorMessage[0]);
    }

    Log::Info("Attaching Fragment Shader...");
    glAttachShader(m_ProgramID, m_FragmentID);
    Log::Success("Attached Fragment Shader!");
}

void Shader::Link() {
    glLinkProgram(m_ProgramID);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Check Linking Status
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if(InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(m_ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        Log::Error(&ProgramErrorMessage[0]);
    }

    glDetachShader(m_ProgramID, m_VertexID);
    glDetachShader(m_ProgramID, m_FragmentID);

    glDeleteShader(m_VertexID);
    glDeleteShader(m_FragmentID);
}

void Shader::Bind() const {
    glUseProgram(m_ProgramID);
}

void Shader::Unbind() {
    glUseProgram(0);
}

void Shader::Dispose() const {
    glUseProgram(0);
    glDeleteProgram(m_ProgramID);
}

void Shader::AddUniformVec4(const char* varName, const glm::vec4& vec4) const {
    auto location = glGetUniformLocation(m_ProgramID, varName);
    glUniform4f(location, vec4.x, vec4.y, vec4.z, vec4.w);
}

void Shader::AddUniformVec3(const char* varName, const glm::vec3& vec3) const {
    auto location = glGetUniformLocation(m_ProgramID, varName);
    glUniform3f(location, vec3.x, vec3.y, vec3.z);
}

void Shader::AddUniformMat4(const char* varName, const glm::mat4& mat4) const {
    auto location = glGetUniformLocation(m_ProgramID, varName);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat4));
}

void Shader::AddUniformInt(const char* varName, const int& integer) const {
    auto location = glGetUniformLocation(m_ProgramID, varName);
    glUniform1i(location, integer);
}

void Shader::AddUniformIntArray(const char* varName, const int& size, const int* array) const {
    auto location = glGetUniformLocation(m_ProgramID, varName);
    glUniform1iv(location, size, array);
}

void Shader::AddUniformUintArray(const char* varName, const int& size, const uint32_t* array) const {
    auto location = glGetUniformLocation(m_ProgramID, varName);
    glUniform1uiv(location, size, array);
}