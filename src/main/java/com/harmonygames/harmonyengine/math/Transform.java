package com.harmonygames.harmonyengine.math;

import org.joml.Vector2f;

public class Transform {

    public Vector2f position;
    public float rotation;
    public Scale scale;

    public Transform(Vector2f position, float rotation, Scale scale) {
        this.position = position;
        this.rotation = rotation;
        this.scale = scale;
    }

    public Transform(Vector2f position, Scale scale) {
        this(position, 0f, scale);
    }

    public Transform() {
        this(new Vector2f(), 0f, new Scale());
    }
}
