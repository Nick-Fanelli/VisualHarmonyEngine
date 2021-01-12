package test;

import com.harmonygames.harmonyengine.object.GameObject;
import com.harmonygames.harmonyengine.object.component.SpriteRenderer;
import com.harmonygames.harmonyengine.render.Sprite;
import com.harmonygames.harmonyengine.render.batches.SpriteRenderBatch;
import com.harmonygames.harmonyengine.scene.Scene;
import org.lwjgl.system.CallbackI;

public class TestScene extends Scene {


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

        GameObject gameObject = new GameObject("Sample Object");
        gameObject.transform.position.set(0, 0);
        gameObject.transform.scale.set(64, 64);

        SpriteRenderer renderer = new SpriteRenderer();
        gameObject.addComponent(renderer);
        renderer.setSprite(new Sprite());

        GameObject object = new GameObject("Sample Object");
        object.transform.position.set(100, 100);
        object.transform.scale.set(128, 64);
        SpriteRenderer renderer1 = new SpriteRenderer();
        object.addComponent(renderer1);
        renderer1.setSprite(new Sprite());


        super.addGameObject(gameObject);
        super.addGameObject(object);

//        shader = Assets.loadShader("/shaders/sprite.glsl");
    }

    @Override
    public void update(float deltaTime) {
        super.update(deltaTime);
    }

}