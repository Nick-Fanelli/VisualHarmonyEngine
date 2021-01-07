package com.harmonygames.harmonyengine.scene;

import com.harmonygames.harmonyengine.objects.Camera;

public abstract class Scene {

    protected Camera mainCamera;

    public void onCreate() {
        mainCamera = new Camera("Main Camera");
    }

    public void update(float deltaTime) {}
    public void onDestroy() {}

    public Camera getMainCamera() { return mainCamera; }

}
