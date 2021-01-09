package com.harmonygames.harmonyengine.object;

import com.harmonygames.harmonyengine.math.Transform;

public class GameObject {

    public final String name;
    public final Transform transform = new Transform();

    public GameObject(String name) {
        this.name = name;
    }

}
