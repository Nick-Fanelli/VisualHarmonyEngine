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

    @Override
    public boolean equals(Object object) {
        if(!(object instanceof Scale)) return false;

        Scale other = (Scale) object;

        return other.width == this.width && other.height == this.height;
    }

    public void set(int width, int height) {
        this.width = width;
        this.height = height;
    }
}
