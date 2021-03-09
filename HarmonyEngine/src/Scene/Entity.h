#pragma once

#include "harmonypch.h"
#include "Scene.h"
#include "Component.h"

namespace HarmonyEngine::Entity {

    template<typename T, typename... Args>
    static T& AddComponent(Scene* scene, const entt::entity& entityID, Args&& ... args) {
        return scene->GetRegistry().emplace<T>(entityID, std::forward<Args>(args)...);
    }

    template<typename T>
    static bool ContainsComponent(Scene* scene, const entt::entity& entityID) {
        return scene->GetRegistry().has<T>(entityID);
    }

    template<typename T>
    static T& GetComponent(Scene* scene, const entt::entity& entityID) {
        if(!ContainsComponent<T>(scene, entityID)) {
            Log::Error("Entity does not contain component!");
        }

        return scene->GetRegistry().template get<T>(entityID);
    }

    template<typename T>
    static void RemoveComponent(Scene* scene, const entt::entity& entityID) {
        if(!ContainsComponent<T>(scene, entityID)) {
            Log::Error("Entity does not contain component!");
        }
        scene->GetRegistry().remove<T>(entityID);
    }

}