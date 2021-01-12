package com.harmonygames.harmonyengine.object.component;

import com.harmonygames.harmonyengine.math.Transform;
import com.harmonygames.harmonyengine.render.Sprite;
import com.harmonygames.harmonyengine.render.Texture;
import org.joml.Vector2f;
import org.joml.Vector4f;

public class SpriteRenderer extends Component {

    private final Vector4f color = new Vector4f(1, 1, 1, 1);
    private Sprite sprite = new Sprite();

    private Transform lastTransform;
    private boolean shouldRedraw = true;

    @Override
    public void onCreate() {
        this.lastTransform = gameObject.transform.copy();
    }

    @Override
    public void update(float deltaTime) {
        if(!this.lastTransform.equals(super.gameObject.transform)) {
            this.gameObject.transform.copy(this.lastTransform);
            this.shouldRedraw = true;
        }
    }

    public Vector4f getColor() { return color; }
    public Texture getTexture() { return sprite.getTexture(); }
    public Vector2f[] getTextureCoords() { return sprite.getTextureCoords(); }
    public boolean shouldRedraw() { return this.shouldRedraw; }

    public void setDrawn() { this.shouldRedraw = false; }

    // TODO: Update so that we check to see if the sprite was actually updated.
    public void setSprite(Sprite sprite) {
        this.sprite = sprite;
        this.shouldRedraw = true;
    }

    public void setColor(Vector4f color) {
        if(!this.color.equals(color)) {
            this.color.set(color);
            this.shouldRedraw = true;
        }
    }

    public void setTexture(Texture texture) { this.sprite.setTexture(texture); }
}
