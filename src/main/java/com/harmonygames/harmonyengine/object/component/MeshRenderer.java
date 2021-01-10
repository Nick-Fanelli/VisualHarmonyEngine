package com.harmonygames.harmonyengine.object.component;

import com.harmonygames.harmonyengine.math.Transform;
import com.harmonygames.harmonyengine.mesh.Mesh2D;

public class MeshRenderer extends Component {

    private Mesh2D mesh = null;

    private Transform lastTransform = new Transform();
    private boolean shouldRedraw = true;

    @Override
    public void onCreate() {
        this.lastTransform = gameObject.transform.copy();
    }

    @Override
    public void update(float deltaTime) {
        if(!this.lastTransform.equals(gameObject.transform)) {
            this.gameObject.transform.copy(lastTransform);
            this.shouldRedraw = true;
        }
    }

    public Mesh2D getMesh() { return this.mesh; }
    public void setMesh(Mesh2D mesh) { this.mesh = mesh; }

    public boolean shouldRedraw() { return this.shouldRedraw; }
    public void setDrawn() { this.shouldRedraw = false; }
}
