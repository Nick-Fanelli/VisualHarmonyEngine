package com.harmonygames.harmonyengine.objects.compoonents;

import com.harmonygames.harmonyengine.render.Texture;
import org.joml.Vector2f;
import org.joml.Vector4f;

public abstract class Renderer extends Component {

    protected Texture texture = null;
    protected boolean shouldRedraw = false;

    protected Vector4f color = new Vector4f(1f, 1f, 1f, 1f);

    public boolean shouldRedraw() { return this.shouldRedraw; }
    public void setDrawn() { this.shouldRedraw = false; }

    public abstract Texture getTexture();
    public abstract Vector2f[] getTextureCoords();

    public void setColor(Vector4f color) {
        if (!this.color.equals(color)) {
            this.color.set(color);
            this.shouldRedraw = true;
        }
    }

    public Vector4f getColor() { return this.color; }
}
