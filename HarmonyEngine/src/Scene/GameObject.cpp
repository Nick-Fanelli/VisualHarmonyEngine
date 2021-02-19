#include "GameObject.h"

#include <entt/entt.hpp>

namespace HarmonyEngine {

    void GameObject::OnCreate(const entt::entity& entityID) {
        m_EntityID = entityID;
    }

    void GameObject::Update(const float& deltaTime) {
    }

    void GameObject::OnDestroy() {
    }

}