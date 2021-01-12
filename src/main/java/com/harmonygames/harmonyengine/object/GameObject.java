package com.harmonygames.harmonyengine.object;

import com.harmonygames.harmonyengine.Log;
import com.harmonygames.harmonyengine.math.Transform;
import com.harmonygames.harmonyengine.object.component.Component;

import java.util.ArrayList;

public class GameObject {

    public final String name;
    public final Transform transform = new Transform();

    private final ArrayList<Component> components = new ArrayList<>();

    protected int zIndex = 0;

    public GameObject(String name) {
        this.name = name;
    }

    public void update(float deltaTime) {
        for(int i = 0; i < components.size(); i++) components.get(i).update(deltaTime);
    }

    public void addComponent(Component component) {
        if(component.isSharable()) {
            component.setGameObject(this);
            component.onCreate();
            this.components.add(component);
        } else if(!component.isSharable() && !this.containsComponentType(component.getClass())) {
            component.setGameObject(this);
            component.onCreate();
            this.components.add(component);
        }
    }

    public <T extends Component> boolean containsComponentType(Class<T> componentType) {
        for(Component component : components) {
            if (componentType.isAssignableFrom(component.getClass())) {
                return true;
            }
        }

        return false;
    }

    public <T extends Component> T getComponent(Class<T> componentType) {
        for(Component component : components) {
            if(componentType.isAssignableFrom(component.getClass())) {
                if(component.isSharable()) Log.warn("Component '" + component.toString() + "' is sharable and there might be more than one that is not be accessed!");
                try {
                    return componentType.cast(component);
                } catch (ClassCastException e) {
                    e.printStackTrace();
                }
            }
        }

        return null;
    }

    public <T extends Component> void removeComponentType(Class<T> componentType) {
        for(int i = 0; i < components.size(); i++) {
            Component component = components.get(i);
            if(componentType.isAssignableFrom(component.getClass())) {
                if(component.isSharable()) Log.warn("Component '" + component.toString() + "' is sharable and there might be more than one that is not be accessed!");
                components.remove(i);
                return;
            }
        }
    }

    public int getzIndex() { return this.zIndex; }
    public void setzIndex(int index) { this.zIndex = zIndex; }

}
