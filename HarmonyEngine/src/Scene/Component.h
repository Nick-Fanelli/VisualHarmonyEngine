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

    MeshRenderer();

    std::shared_ptr<Mesh2D> m_Mesh = nullptr;

    void OnCreate() override;
    void Update(const float& deltaTime) override;
    void OnDestroy() override;

public:
    MeshRenderer(std::shared_ptr<Mesh2D> mesh) : m_Mesh(mesh) {}

    const std::shared_ptr<Mesh2D>& GetMesh() const { return m_Mesh; }

};