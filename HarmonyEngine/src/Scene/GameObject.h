#pragma once

#include <string>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "../Core/Log.h"
#include "Scene.h"
#include "Component.h"

#include <entt/entt.hpp>

namespace HarmonyEngine {

    class GameObject {

        Scene* m_ParentScene;
        std::string m_Name;
        glm::vec2 m_Position;
        entt::entity m_EntityID;

    public:
        GameObject(std::string name) : m_Name(name), m_Position(glm::vec2()) {}

        virtual ~GameObject() { OnDestroy(); }

        virtual void OnCreate(const entt::entity& entityID);

        virtual void Update(const float& deltaTime);

        virtual void OnDestroy();

        const Scene* GetParentScene() const { return m_ParentScene; }

        const std::string& GetName() const { return m_Name; }

        const glm::vec2& GetPosition() const { return m_Position; }

        const void SetPosition(const glm::vec2& position) { m_Position = position; }

        void SetParentScene(Scene* scene) { m_ParentScene = scene; }

        template<typename T, typename... Args>
        T& AddComponent(Args&& ... args) {
            return m_ParentScene->m_Registry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
        }

        template<typename T>
        T& GetComponent() {
            if (!ContainsComponent<T>()) {
                Log::Error("Entity does not contain component!");
                exit(-1);
            }

            return m_ParentScene->m_Registry.get<T>(m_EntityID);
        }

        template<typename T>
        bool ContainsComponent() {
            return m_ParentScene->m_Registry.has<T>(m_EntityID);
        }

        template<typename T>
        void RemoveComponent() {
            if (!ContainsComponent<T>()) {
                Log::Error("Entity does not contain component!");
                exit(-1);
            }
            m_ParentScene->m_Registry.remove<T>(m_EntityID);
        }
    };
}