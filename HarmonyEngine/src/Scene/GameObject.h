#pragma once

class GameObject {

    virtual void OnCreate();
    virtual void Update(const float& deltaTime);
    virtual void OnDestroy();

};