package com.harmonygames.harmonyengine.object.component;

import com.harmonygames.harmonyengine.object.GameObject;

public abstract class Component {

    private GameObject gameObject = null;

    public abstract void update(float deltaTime);

    public void setGameObject(GameObject gameObject) { this.gameObject = gameObject; }
    public GameObject getGameObject() { return this.gameObject; }

}