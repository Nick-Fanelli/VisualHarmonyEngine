#include "Shader.h"

#include <vector>
#include "../Core/Log.h"

void Shader::AttachVertexShader(const std::string& source) {
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

void Shader::AttachFragmentShader(const std::string& source) {
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

void Shader::Bind() {
    glUseProgram(m_ProgramID);
}

void Shader::Unbind() {
    glUseProgram(0);
}

void Shader::Dispose() {
    glUseProgram(0);

    glDeleteProgram(m_ProgramID);
}