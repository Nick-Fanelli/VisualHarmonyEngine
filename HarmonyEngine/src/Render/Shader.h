#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLUT/glut.h>

#include <string>

class Shader {

    GLuint m_ProgramID, m_VertexID, m_FragmentID;

    void AttachVertexShader(const std::string& source);
    void AttachFragmentShader(const std::string& source);
    void Link();

public:
    Shader(const std::string& vertexSource, const std::string& fragmentSource) {
        m_ProgramID = glCreateProgram();
        AttachVertexShader(vertexSource);
        AttachFragmentShader(fragmentSource);
        Link();
    }

    void Bind();
    void Unbind();
    void Dispose();

};