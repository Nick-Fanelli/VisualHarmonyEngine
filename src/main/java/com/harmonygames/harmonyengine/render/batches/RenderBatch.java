package com.harmonygames.harmonyengine.render.batches;

import com.harmonygames.harmonyengine.object.component.Component;
import com.harmonygames.harmonyengine.object.component.MeshRenderer;

import java.util.ArrayList;

public abstract class RenderBatch<T extends Component> {

    public static final int RENDER_BATCH_CAPACITY = 1000;

    protected ArrayList<T> renderComponents = new ArrayList<>();
    protected int size = 0;
    protected final int zIndex;

    public RenderBatch(int zIndex) {
        this.zIndex = zIndex;
    }

    public abstract void onCreate();
    public abstract void addRenderComponent(T component);
    public abstract void removeRenderComponent(T component);
    public abstract void onDestroy();

    public int getSize() { return this.size; }
    public boolean isFull() { return this.size < RENDER_BATCH_CAPACITY; }

    public int getzIndex() { return this.zIndex; }
}
