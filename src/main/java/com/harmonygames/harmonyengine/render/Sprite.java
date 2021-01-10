package com.harmonygames.harmonyengine.render;

import org.joml.Vector2f;

public class Sprite {

    public static final Vector2f[] DEFAULT_QUAD_TEXTURE_COORDS = {
            new Vector2f(1, 1),
            new Vector2f(1, 0),
            new Vector2f(0, 0),
            new Vector2f(0, 1)
    };

    private float width, height;

    private Texture texture = null;
    private Vector2f[] textureCoords = DEFAULT_QUAD_TEXTURE_COORDS;

    public Texture getTexture() { return this.texture; }
    public Vector2f[] getTextureCoords() { return this.textureCoords; }

    public void setTexture(Texture texture) { this.texture = texture; }
    public void setTextureCoords(Vector2f[] textureCoords) { this.textureCoords = textureCoords; }

    public float getWidth() { return this.width; }
    public float getHeight() { return this.height; }

    public void setWidth(float width) { this.width = width; }
    public void setHeight(float height) { this.height = height; }

    public int getTextureID() { return texture == null ? -1 : texture.getTextureID(); }

}
