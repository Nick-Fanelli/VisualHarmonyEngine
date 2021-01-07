package com.harmonygames.harmonyengine.objects;

import com.harmonygames.harmonyengine.Log;
import com.harmonygames.harmonyengine.math.Transform;
import com.harmonygames.harmonyengine.objects.compoonents.Component;

import java.util.ArrayList;

public class GameObject {

    public final String name;
    public Transform transform;

    private final ArrayList<Component> components = new ArrayList<>();

    public GameObject(String name, Transform transform) {
        this.name = name;
        this.transform = transform;
    }

    public void update(float deltaTime) {
        for(int i = 0; i < components.size(); i++) components.get(i).update(deltaTime);
    }

    public void addComponent(Component component) {
        if(component.shouldAdd(this)) {
            component.setGameObject(this);
            component.start();
            components.add(component);
        }
        else Log.warn("Component with type '" + component.getClass().getName() + "' wasn't added because it refused!");
    }

    public <T extends Component> boolean containsComponent(Class<T> componentClass) {
        for(Component component : components) {
            if(component.getClass().equals(componentClass)) return true;
        }

        return false;
    }

    public <T extends Component> Component getComponent(Class<T> componentClass) {
        for(Component component : components) {
            if(component.getClass().equals(componentClass)) return component;
        }

        return null;
    }
}
