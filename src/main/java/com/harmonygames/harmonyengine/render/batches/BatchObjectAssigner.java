package com.harmonygames.harmonyengine.render.batches;

import com.harmonygames.harmonyengine.object.GameObject;
import com.harmonygames.harmonyengine.object.component.SpriteRenderer;
import com.harmonygames.harmonyengine.scene.Scene;

import java.util.ArrayList;

public class BatchObjectAssigner {

    private final Scene scene;
    private final ArrayList<RenderBatch<?>> renderBatches;

    public BatchObjectAssigner(Scene scene) {
        this.scene = scene;
        this.renderBatches = new ArrayList<>();
    }

    // TODO: Extend to different types of render components
    public void assignGameObject(GameObject gameObject) {
        SpriteRenderer renderer = gameObject.getComponent(SpriteRenderer.class);
        if(renderer == null) return;

        for(RenderBatch<?> batch : renderBatches) {
            if(batch.zIndex == gameObject.getzIndex()) {
                if(batch.getClass().isAssignableFrom(SpriteRenderer.class)) {
                    if(!batch.isFull()) {
                        ((SpriteRenderBatch) (batch)).addRenderComponent(renderer);
                        return;
                    }
                }
            }
        }

        SpriteRenderBatch batch = new SpriteRenderBatch(scene, gameObject.getzIndex());
        batch.addRenderComponent(renderer);
        renderBatches.add(batch);
    }

}
