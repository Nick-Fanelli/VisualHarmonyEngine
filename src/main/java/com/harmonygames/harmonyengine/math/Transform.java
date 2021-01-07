package com.harmonygames.harmonyengine.math;

import org.joml.Vector2f;
import org.lwjgl.system.CallbackI;

public class Transform {

    public Vector2f position;
    public Scale scale;

    public Transform(Vector2f position, Scale scale) {
        this.position = position;
        this.scale = scale;
    }

    public Transform() {
        this.position = new Vector2f();
        this.scale = new Scale();
    }

    public void set(Vector2f position, Scale scale) {
        this.position = position;
        this.scale = scale;
    }
}
