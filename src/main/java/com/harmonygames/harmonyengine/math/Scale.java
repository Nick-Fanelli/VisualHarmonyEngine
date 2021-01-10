package com.harmonygames.harmonyengine.math;

public class Scale {

    public int width;
    public int height;

    public Scale(Scale scale) {
        this.width = scale.width;
        this.height = scale.height;
    }

    public Scale(int width, int height) {
        this.width = width;
        this.height = height;
    }

    public Scale() {
        this(0, 0);
    }

}
