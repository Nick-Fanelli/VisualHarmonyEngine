#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <vector>
#include <glm/glm.hpp>

// ======================================================================================
// Vertex Struct
// ======================================================================================

static const int VERTEX_FLOAT_COUNT = 6;

struct Vertex {

    glm::vec2 Position;
    glm::vec4 Color;

};

// ======================================================================================
// Mesh2D
// ======================================================================================

class Mesh2D {

    std::vector<Vertex>* m_Vertices;
    std::vector<uint32_t>* m_Indices;

public:
    Mesh2D(std::vector<Vertex>* vertices, std::vector<uint32_t>* indices)
    : m_Vertices(vertices), m_Indices(indices) {

    }

    // const std::vector<Vertex>* GetVertices() const { return m_Vertices; }
    // const std::vector<uint32_t>* GetIndices() const { return m_Indices; }

    std::vector<Vertex>* GetVertices() const { return m_Vertices; }
    std::vector<uint32_t>* GetIndices() const { return m_Indices; }

};