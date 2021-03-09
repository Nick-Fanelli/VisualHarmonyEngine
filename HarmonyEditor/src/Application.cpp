#include "HarmonyEngine.h"

#include "EditorScene.h"

int main() {
    GameContext gameContext = GameContext();
    EditorScene scene = EditorScene();

    gameContext.Start(&scene);
}