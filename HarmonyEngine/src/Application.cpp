#include "HarmonyEngine.h"

#include "TestScene.h"

#include <iostream>

static std::vector<Component> components;

template <typename T, typename... Args>
static T& CreateComponent(Args&&... args) {

    components.push_back(T(std::forward<Args>(args)...));
    return *static_cast<T*>(&components.at(components.size() - 1));
    
}

int main() {
    QuadRenderer& quadRenderer = CreateComponent<QuadRenderer>();
    std::cout << &quadRenderer << std::endl;

    // GameContext context = GameContext();
    // TestScene testScene = TestScene();

    // context.Start(&testScene);
}