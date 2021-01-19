#include "Mesh.h"

// ======================================================================================
// Mesh2D
// ======================================================================================

Mesh2D::Mesh2D(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) : m_IndicesCount(indices.size()) {
    // Bind the VAO
    glGenVertexArrays(1, &m_VaoID);
    glBindVertexArray(m_VaoID);

    // Bind the Verticies
    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind Vertex Buffer

    // Push the data
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, (void*) 0); 

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind Buffer

    // Bind the indices
    glGenBuffers(1, &m_EboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboID); // Bind Indicies Buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind Buffer
}