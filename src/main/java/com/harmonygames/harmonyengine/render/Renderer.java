package com.harmonygames.harmonyengine.render;

import com.harmonygames.harmonyengine.objects.Component;

public abstract class Renderer extends Component {

    protected Texture texture = null;
    protected boolean shouldRedraw = false;

    public abstract void loadVertexProperties(int index);

    public boolean shouldRedraw() { return this.shouldRedraw; }
    public void setDrawn() { this.shouldRedraw = false; }

    public Texture getTexture() { return this.texture; }

}
