package com.harmonygames.harmonyengine.scene;

public class SceneManager {

    private static Scene activeScene;

    public static void setActiveScene(Scene scene) {
        if(activeScene != null) activeScene.onDestroy();

        scene.onCreate();
        activeScene = scene;
    }

    public void update(float deltaTime) {
        if(activeScene != null)
            activeScene.update(deltaTime);
    }

    public void cleanUp() {
        if(activeScene != null) activeScene.onDestroy();
        activeScene = null;
    }

    public static Scene getActiveScene() { return activeScene; }

}
