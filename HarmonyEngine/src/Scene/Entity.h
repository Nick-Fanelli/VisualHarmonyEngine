#pragma once

#include "harmonypch.h"
#include "Scene.h"
#include "Component.h"

namespace HarmonyEngine::Entity {

    template<typename T, typename... Args>
    static T& AddComponent(Scene* scene, const entt::entity& entityID, Args&& ... args) {
        return scene->m_Registry.emplace<T>(entityID, std::forward<Args>(args)...);
    }

    template<typename T>
    static bool ContainsComponent(Scene* scene, const entt::entity& entityID) {
        return scene->m_Registry.has<T>(entityID);
    }

    template<typename T>
    static T& GetComponent(Scene* scene, const entt::entity& entityID) {
        if(!ContainsComponent<T>(scene, entityID)) {
            Log::Error("Entity does not contain component!");
            exit(-1);
        }

        return scene->m_Registry.template get<T>(entityID);
    }

    template<typename T>
    static void RemoveComponent(Scene* scene, const entt::entity& entityID) {
        if(!ContainsComponent<T>(scene, entityID)) {
            Log::Error("Entity does not contain component!");
            exit(-1);
        }
        scene->m_Registry.remove<T>(entityID);
    }

}