package com.harmonygames.harmonyengine.math;

public class Scale {

    public int width;
    public int height;

    public Scale(int width, int height) {
        this.width = width;
        this.height = height;
    }

    public Scale() { this(0, 0); }

    public Scale copy() { return new Scale(this.width, this.height); }

}
