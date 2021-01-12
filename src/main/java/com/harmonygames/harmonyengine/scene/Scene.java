package com.harmonygames.harmonyengine.scene;

import com.harmonygames.harmonyengine.object.Camera;

public abstract class Scene {

    protected Camera mainCamera = new Camera("Main Camera");

    public void onCreate() {}

    public void update(float deltaTime) {
        mainCamera.update(deltaTime);
    }

    public void onDestroy() {}

    public Camera getMainCamera() { return this.mainCamera; }
}
