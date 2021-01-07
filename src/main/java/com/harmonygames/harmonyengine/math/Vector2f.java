package com.harmonygames.harmonyengine.math;

public class Vector2f {

    public float x;
    public float y;

    public Vector2f(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public Vector2f() { this(0, 0); }

    public Vector2f copy() { return new Vector2f(this.x, this.y); }
}
