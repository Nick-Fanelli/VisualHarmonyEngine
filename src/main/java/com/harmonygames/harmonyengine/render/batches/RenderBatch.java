package com.harmonygames.harmonyengine.render.batches;

import com.harmonygames.harmonyengine.object.component.Component;
import com.harmonygames.harmonyengine.scene.Scene;

public abstract class RenderBatch<T extends Component> {

    public static final int RENDER_BATCH_CAPACITY = 1000;

    protected final Scene scene;
    protected final int zIndex;

    protected int size = 0;

    public RenderBatch(Scene scene, int zIndex) {
        this.scene = scene;
        this.zIndex = zIndex;
    }

    public abstract void onCreate();
    public abstract void addRenderComponent(T component);
    public abstract void render();
    public abstract void removeRenderComponent(T component);
    public abstract void onDestroy();

    public int getSize() { return this.size; }
    public boolean isFull() { return this.size < RENDER_BATCH_CAPACITY; }

    public int getzIndex() { return this.zIndex; }
}
