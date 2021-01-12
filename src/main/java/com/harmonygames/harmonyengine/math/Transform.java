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

    public Transform copy(Transform transform) {
        transform.position = new Vector2f(this.position);
        transform.scale = new Scale(this.scale);
        transform.rotation = this.rotation;
        return transform;
    }

    public Transform copy() {
        return new Transform(new Vector2f(position), rotation, new Scale(scale));
    }

    @Override
    public boolean equals(Object object) {
        if(!(object instanceof Transform)) return false;
        Transform other = (Transform) object;

        return other.position.equals(this.position) && other.scale.equals(this.scale);
    }
}
