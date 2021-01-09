package com.harmonygames.harmonyengine.math;

import org.joml.Vector3f;

public class Transform {

    public Vector3f position;
    public Vector3f rotation;
    public Scale scale;

    public Transform(Vector3f position, Vector3f rotation, Scale scale) {
        this.position = position;
        this.rotation = rotation;
        this.scale = scale;
    }

    public Transform(Vector3f position, Scale scale) {
        this(position, new Vector3f(), scale);
    }

    public Transform() {
        this(new Vector3f(), new Vector3f(), new Scale());
    }
}
