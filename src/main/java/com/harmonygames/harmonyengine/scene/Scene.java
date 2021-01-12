package com.harmonygames.harmonyengine.scene;

import com.harmonygames.harmonyengine.object.Camera;
import com.harmonygames.harmonyengine.object.GameObject;
import com.harmonygames.harmonyengine.render.batches.BatchObjectAssigner;

import java.util.ArrayList;

public abstract class Scene {

    protected Camera mainCamera = new Camera("Main Camera");

    private final BatchObjectAssigner objectAssigner;
    private final ArrayList<GameObject> gameObjects;

    public Scene() {
        this.objectAssigner = new BatchObjectAssigner(this);
        this.gameObjects = new ArrayList<>();
    }

    public void onCreate() {}

    public void update(float deltaTime) {
        mainCamera.update(deltaTime);
        for(GameObject gameObject : gameObjects) gameObject.update(deltaTime);
        objectAssigner.render();
    }

    public void onDestroy() {
        //TODO: IMPLEMENT
//        for(GameObject gameObject : gameObjects) gameObject.onDestroy()
    }

    public Camera getMainCamera() { return this.mainCamera; }

    public void addGameObject(GameObject gameObject) {
        this.objectAssigner.assignGameObject(gameObject);
        this.gameObjects.add(gameObject);
    }
}
