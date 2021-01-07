package com.harmonygames.harmonyengine.objects;

import com.harmonygames.harmonyengine.math.Transform;

public class GameObject {

    public final String name;
    public Transform transform;

    public GameObject(String name, Transform transform) {
        this.name = name;
        this.transform = transform;
    }

    public void update() {

    }

}
