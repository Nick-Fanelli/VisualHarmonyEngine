#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "../Render/Renderer.h"

class GameObject;

// ======================================================================================
// Component Class
// ======================================================================================
class Component {

    friend class GameObject;

    GameObject* m_ParentObject = nullptr;

private:
    void SetParentObject(GameObject* parent) { m_ParentObject = parent; }

public:
    GameObject* GetParentGameObject();

    virtual void OnCreate();
    virtual void Update(const float& deltaTime);
    virtual void OnDestroy();

    virtual ~Component() {}
};

// ======================================================================================
// Quad Renderer Componet
// ======================================================================================
class QuadRenderer : public Component {

    Quad m_Quad;

public:
    QuadRenderer(const Quad& quad) : m_Quad(quad) {

    }

    void OnCreate() override;
    void Update(const float& deltaTime) override;
    void OnDestroy() override;

};