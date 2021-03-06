//
// Created by Nick Fanelli on 3/6/21.
//

#pragma once

#include "harmonypch.h"

namespace HarmonyEngine {

    struct HierarchalNode {

        entt::entity GameObject;
        std::vector<HierarchalNode> Children;

        HierarchalNode() = default;
        HierarchalNode(const HierarchalNode&) = default;
        HierarchalNode(const entt::entity& GameObject) : GameObject(GameObject), Children() {}

        void AddChildGameObject(const entt::entity& GameObjectRef) { Children.emplace_back(GameObjectRef); }

    };

    struct Hierarchy {

        HierarchalNode RootNode;

        Hierarchy() : RootNode() {}
        Hierarchy(const Hierarchy&) = default;

        void AddGameObject(const entt::entity& GameObjectRef) {
            RootNode.AddChildGameObject(GameObjectRef);
        }

    };

};