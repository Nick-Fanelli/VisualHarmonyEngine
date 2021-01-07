package com.harmonygames.harmonyengine.objects.compoonents;

import com.harmonygames.harmonyengine.objects.GameObject;

public abstract class Component {

    private GameObject gameObject = null;

    public abstract void start();

    public abstract void update(float deltaTime);
    public abstract boolean shouldAdd(GameObject gameObject);

    public void setGameObject(GameObject gameObject) { this.gameObject = gameObject; }
    public GameObject getGameObject() { return this.gameObject; }

}
