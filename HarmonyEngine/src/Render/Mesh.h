#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <vector>

// ======================================================================================
// Mesh2D
// ======================================================================================

class Mesh2D {

    int m_IndicesCount;
    GLuint m_VaoID;
    GLuint m_EboID;

public:
    Mesh2D(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

    const GLuint& GetVaoID() const { return m_VaoID; }
    const GLuint& GetEboID() const { return m_EboID; }

    const int& GetIndicesCount() const { return m_IndicesCount; }
};