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

    std::vector<float>* m_Vertices;
    std::vector<uint32_t>* m_Indices;

public:
    Mesh2D(std::vector<float>* vertices, std::vector<uint32_t>* indices) 
        : m_IndicesCount((*indices).size()), m_VaoID(0), m_EboID(0), m_Vertices(vertices), m_Indices(indices) {
        
    }

    void Initialize() {
        // Bind the VAO
        glGenVertexArrays(1, &m_VaoID);
        glBindVertexArray(m_VaoID);

        // Bind the Verticies
        GLuint vboID;
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind Vertex Buffer

        // Push the data
        glBufferData(GL_ARRAY_BUFFER, (*m_Vertices).size() * sizeof((*m_Vertices)[0]), &((*m_Vertices)[0]), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, (void*) 0); 

        glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind Buffer

        // Bind the indices
        glGenBuffers(1, &m_EboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboID); // Bind Indicies Buffer
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (*m_Indices).size() * sizeof(uint32_t), &((*m_Indices)[0]), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind Buffer
        glBindVertexArray(0);
    }

    const GLuint& GetVaoID() const { return m_VaoID; }
    const GLuint& GetEboID() const { return m_EboID; }

    const int& GetIndicesCount() const { return m_IndicesCount; }
};