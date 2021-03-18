#include "EditorScene.h"

using namespace HarmonyEngine;
using namespace HarmonyEditor;

int main() {
    GameContext gameContext = GameContext();
    EditorScene scene = EditorScene();

    gameContext.Start(&scene);
}