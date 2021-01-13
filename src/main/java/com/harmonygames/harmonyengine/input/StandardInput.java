package com.harmonygames.harmonyengine.input;

import com.harmonygames.harmonyengine.Log;
import org.joml.Vector2f;
import org.lwjgl.glfw.GLFW;

public class StandardInput {

    private static final boolean[] keys = new boolean[350];
    private static final boolean[] mouseButtons = new boolean[9];

    private static final Vector2f mousePosition = new Vector2f();
    private static final Vector2f lastMousePosition = new Vector2f();
    private static final Vector2f scrollPosition = new Vector2f();

    private static boolean isDragging = false;

    // TODO: Implement
//    private Vector2f gameViewportPosition = new Vector2f();
//    private Vector2f gameViewportSize     = new Vector2f();

    public void keyCallback(long window, int key, int scanCode, int action, int mods) {
        if(action == GLFW.GLFW_PRESS) {
            keys[key] = true;
        } else if(action == GLFW.GLFW_RELEASE) {
            keys[key] = false;
        }
    }

    public void mousePositionCallback(long window, double xPos, double yPos) {
        lastMousePosition.set(new Vector2f(mousePosition));
        mousePosition.set(xPos, yPos);
        isDragging = (mouseButtons[0] || mouseButtons[1] || mouseButtons[2]);
    }

    public void mouseButtonCallback(long window, int button, int action, int mods) {
        if(action == GLFW.GLFW_PRESS) {
            if(button < mouseButtons.length) mouseButtons[button] = true;
        } else if(action == GLFW.GLFW_RELEASE) {
            if(button < mouseButtons.length) {
                mouseButtons[button] = false;
                if(!mouseButtons[0] && !mouseButtons[1] && !mouseButtons[2]) isDragging = false;
            }
        }
    }

    public void mouseScrollCallback(long window, double xOffset, double yOffset) {
        scrollPosition.set(xOffset, yOffset);
    }

    public void endFrame() {
        scrollPosition.zero();
        lastMousePosition.set(new Vector2f(mousePosition));
    }

    public static boolean isKeyPressed(int keycode) {
        return keys[keycode];
    }

    public static Vector2f getMousePosition() { return mousePosition; }
    public static Vector2f getDeltaMousePosition() { return new Vector2f(lastMousePosition).sub(mousePosition); }
    public static Vector2f getScroll() { return scrollPosition; }

    public static boolean isDragging() { return isDragging; }

    public static boolean mouseButtonDown(int button) {
        if (button < mouseButtons.length) return mouseButtons[button];
        else {
            Log.warn("Unknown mouse button value of '" + button + "'");
            return false;
        }
    }
}
