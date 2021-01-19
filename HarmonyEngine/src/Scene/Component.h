#pragma once

#include <memory>
#include "../Render/Mesh.h"
#include "../Render/Shader.h"

class GameObject;

// ======================================================================================
// Component Class
// ======================================================================================
class Component {

    friend class GameObject;

    GameObject* m_ParentObject = nullptr;

private:
    void SetParentObject(GameObject* parent) { m_ParentObject = parent; }

protected:
    virtual void OnCreate();
    virtual void Update(const float& deltaTime);
    virtual void OnDestroy();

public:
    const GameObject* GetParentGameObject() const { return m_ParentObject; }
};

// ======================================================================================
// Mesh Renderer Component
// ======================================================================================
class MeshRenderer : public Component {

    static std::shared_ptr<Shader> s_DefaultShader;
    std::shared_ptr<Shader> m_Shader;

    std::shared_ptr<Mesh2D> m_Mesh;

    void OnCreate() override;
    void Update(const float& deltaTime) override;
    void OnDestroy() override;

public:
    MeshRenderer(std::shared_ptr<Mesh2D> mesh, std::shared_ptr<Shader> shader) : m_Mesh(mesh), m_Shader(shader) {}
    MeshRenderer(std::shared_ptr<Mesh2D> mesh);

    const std::shared_ptr<Mesh2D>& GetMesh() const { return m_Mesh; }

};