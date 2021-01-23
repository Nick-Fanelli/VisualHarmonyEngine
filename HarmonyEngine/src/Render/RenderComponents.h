#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "../Scene/Component.h"
#include "Shader.h"
#include "Mesh.h"

// ======================================================================================
// Mesh Renderer Component
// ======================================================================================
class MeshRenderer : public Component {

    static std::shared_ptr<Shader> s_DefaultShader;

    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Mesh2D> m_Mesh;
    glm::vec4 m_Color;

    void OnCreate() override;
    void Update(const float& deltaTime) override;
    void OnDestroy() override;

public:
    MeshRenderer(std::shared_ptr<Mesh2D> mesh, std::shared_ptr<Shader> shader, glm::vec4 color) : m_Shader(shader), m_Mesh(mesh), m_Color(color) {}
    MeshRenderer(std::shared_ptr<Mesh2D> mesh, std::shared_ptr<Shader> shader) : m_Shader(shader), m_Mesh(mesh) {}
    MeshRenderer(std::shared_ptr<Mesh2D> mesh);

    virtual ~MeshRenderer() {}

    const std::shared_ptr<Mesh2D>& GetMesh() const { return m_Mesh; }

    void SetColor(glm::vec4 color) { m_Color = color; }
};