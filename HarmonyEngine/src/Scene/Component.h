#pragma once

#include <glm/glm.hpp>
#include <memory>

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
    GameObject* GetParentGameObject();

    virtual ~Component() {}
};

class QuadRenderer : public Component {

};