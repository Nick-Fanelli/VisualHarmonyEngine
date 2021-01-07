package com.harmonygames.harmonyengine.objects.compoonents;

import com.harmonygames.harmonyengine.math.Transform;
import com.harmonygames.harmonyengine.objects.GameObject;
import com.harmonygames.harmonyengine.render.Texture;
import org.joml.Vector2f;

import org.joml.Vector2f;
import org.joml.Vector4f;

public class SpriteRenderer extends Component {

    private Vector4f color = new Vector4f(1, 1, 1, 1);
    private Sprite sprite = new Sprite();

    private transient Transform lastTransform;
    private transient boolean shouldRedraw = true;


//    public SpriteRenderer(Vector4f color) {
//        this.color = color;
//        this.sprite = new Sprite(null);
//        this.shouldRedraw = true;
//    }
//
//    public SpriteRenderer(Sprite sprite) {
//        this.sprite = sprite;
//        this.color = new Vector4f(1, 1, 1, 1);
//        this.shouldRedraw = true;
//    }

    @Override
    public void start() {
        this.lastTransform = getGameObject().transform.copy();
    }

    @Override
    public void update(float deltaTime) {
        if(!this.lastTransform.equals(this.getGameObject().transform)) {
            this.getGameObject().transform.copy(this.lastTransform);
            this.shouldRedraw = true;
        }
    }

    public Vector4f getColor() { return color; }
    public Texture getTexture() {
        return sprite.getTexture();
    }
    public Vector2f[] getTexCoords() {
        return sprite.getTexCoords();
    }
    public boolean shouldRedraw() { return this.shouldRedraw; }

    public void setDrawn() { this.shouldRedraw = false; }

    // TODO: Update so that we check to see if sprite was actually updated.
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

}