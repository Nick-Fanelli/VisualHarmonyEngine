#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "../Scene/Component.h"
#include "Shader.h"
#include "Mesh.h"
#include "Sprite.h"
#include "../Scene/Camera.h"

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
    MeshRenderer(std::shared_ptr<Mesh2D> mesh, std::shared_ptr<Shader> shader) : m_Shader(shader), m_Mesh(mesh), m_Color(glm::vec4(1, 1, 1, 1)) {}
    MeshRenderer(std::shared_ptr<Mesh2D> mesh);

    virtual ~MeshRenderer() {}

    const std::shared_ptr<Mesh2D>& GetMesh() const { return m_Mesh; }

    void SetColor(glm::vec4 color) { m_Color = color; }
};

// ======================================================================================
// Sprite Renderer Component
// ======================================================================================
class SpriteRenderer : public Component {

    static std::shared_ptr<Shader> s_DefaultShader;

    Shader* m_Shader;
    Sprite* m_Sprite;
    glm::vec4 m_Color;
    OrthographicCamera* m_Camera; 

    void OnCreate() override;
    void Update(const float& deltaTime) override;
    void OnDestroy() override;

public:
    SpriteRenderer(Sprite* sprite, Shader* shader, glm::vec4 color) : m_Shader(shader), m_Sprite(sprite), m_Color(color) {}
    SpriteRenderer(Sprite* sprite, Shader* shader) : m_Shader(shader), m_Sprite(sprite), m_Color(glm::vec4(1, 1, 1, 1)) {}

    SpriteRenderer(Sprite* sprite) : m_Sprite(sprite), m_Color(glm::vec4(1, 1, 1, 1)) {}

    void Initialize(OrthographicCamera* camera) {
        if(s_DefaultShader == nullptr) {
            s_DefaultShader = std::make_shared<Shader>("assets/shaders/default.vert.glsl", "assets/shaders/default.frag.glsl");
        }

        m_Camera = camera;
        m_Shader = s_DefaultShader.get();
    }

    const Sprite* GetSprite() const { return m_Sprite; }
    void SetSprite(Sprite* sprite) { m_Sprite = sprite; }
    void SetColor(glm::vec4 color) { m_Color = color; }

    virtual ~SpriteRenderer() {}
};