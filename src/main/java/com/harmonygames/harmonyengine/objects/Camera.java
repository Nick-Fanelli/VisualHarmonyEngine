package com.harmonygames.harmonyengine.objects;

import com.harmonygames.harmonyengine.math.Transform;
import com.harmonygames.harmonyengine.math.Vector2f;
import org.joml.Matrix4f;
import org.joml.Vector3f;

public class Camera extends GameObject {

    private Matrix4f projectionMatrix, viewMatrix, inverseProjection, inverseView;
    private Vector2f projectionSize = new Vector2f(32.0f * 40.f, 32.0f * 21.0f);

    public Camera(String name) {
        super(name, new Transform());

        this.projectionMatrix = new Matrix4f();
        this.viewMatrix = new Matrix4f();
        this.inverseProjection = new Matrix4f();
        this.inverseView = new Matrix4f();

        this.adjustProjection();
    }

    public void adjustProjection() {
        projectionMatrix.identity();
        projectionMatrix.ortho(0.0f, projectionSize.x, 0.0f, projectionSize.y, 0.0f, 100.0f);
        projectionMatrix.invert(inverseProjection);
    }

    public Matrix4f getViewMatrix() {
        Vector3f cameraFront = new Vector3f(0.0f, 0.0f, -1.0f);
        Vector3f cameraUp = new Vector3f(0.0f, 1.0f, 0.0f);
        this.viewMatrix.identity();
        this.viewMatrix.lookAt(new Vector3f(transform.position.x, transform.position.y, 20.0f),
                cameraFront.add(transform.position.x, transform.position.y, 0.0f),
                cameraUp);
        this.viewMatrix.invert(inverseView);
        return this.viewMatrix;
    }

    public Matrix4f getProjectionMatrix() { return this.projectionMatrix; }
    public Matrix4f getInverseProjection() { return this.inverseProjection; }
    public Matrix4f getInverseView() { return this.inverseView; }

    public Vector2f getProjectionSize() { return this.projectionSize; }

}
