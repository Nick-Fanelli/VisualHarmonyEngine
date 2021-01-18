#include "HarmonyEngine.h"

#include "TestScene.h"

int main() {
    GameContext context = GameContext();
    TestScene testScene = TestScene();

    context.Start(&testScene);
}