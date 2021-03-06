#include "GameObject.h"

namespace HarmonyEngine {

    void GameObject::OnCreate(const entt::entity& entityID) {
        m_EntityID = entityID;
    }

    void GameObject::Update(const float& deltaTime) {
    }

    void GameObject::OnDestroy() {
    }

}