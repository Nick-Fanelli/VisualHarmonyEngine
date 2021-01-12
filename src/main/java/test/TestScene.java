package test;

import com.harmonygames.harmonyengine.mesh.Mesh2D;
import com.harmonygames.harmonyengine.object.Camera;
import com.harmonygames.harmonyengine.object.GameObject;
import com.harmonygames.harmonyengine.object.component.SpriteRenderer;
import com.harmonygames.harmonyengine.render.Shader;
import com.harmonygames.harmonyengine.render.Sprite;
import com.harmonygames.harmonyengine.render.batches.SpriteRenderBatch;
import com.harmonygames.harmonyengine.scene.Scene;
import org.joml.Vector4f;

public class TestScene extends Scene {

    private GameObject gameObject;
    private SpriteRenderBatch spriteRenderBatch;

//    float[] vertices = {
//            -0.8f, 0.5f,    // Left top         ID: 0
//            -0.8f, -0.5f,    // Left bottom      ID: 1
//            -0.25f, -0.5f,     // Right bottom     ID: 2
//            -0.25f, 0.5f,     // Right left       ID: 3
//
////            0.8f, 0.5f,
////            0.8f, -0.5f,
////            0.25f, -0.5f,
////            0.25f, 0.5f
//    };
//
//    Vector4f color = new Vector4f(1, 0, 0, 1);
//
//    int[] indices = {
//            // Left bottom triangle
//            0, 1, 2,
//            // Right top triangle
//            2, 3, 0,
//
////            4, 5, 6,
////            6, 7, 4
//    };

    @Override
    public void onCreate() {

        mainCamera.transform.position.set(0, 0);

        super.onCreate();

        spriteRenderBatch = new SpriteRenderBatch(this, 0);
        spriteRenderBatch.onCreate();

        gameObject = new GameObject("Sample Object");
        gameObject.transform.position.set(0, 0);
        gameObject.transform.scale.set(64, 64);

        SpriteRenderer renderer = new SpriteRenderer();
        gameObject.addComponent(renderer);
        renderer.setSprite(new Sprite());

        spriteRenderBatch.addRenderComponent(renderer);

//        shader = Assets.loadShader("/shaders/sprite.glsl");
    }

    @Override
    public void update(float deltaTime) {
        super.update(deltaTime);

        gameObject.update(deltaTime);
        spriteRenderBatch.render();
    }

}