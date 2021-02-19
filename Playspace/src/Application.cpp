#include "HarmonyEngine.h"

#include "TestScene.h"

 int main() {
     GameContext gameContext = GameContext();
     TestScene testScene = TestScene();

     gameContext.Start(&testScene);
 }