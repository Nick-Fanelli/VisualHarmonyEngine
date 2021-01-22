#pragma once

#include <vector>
#include "RenderComponents.h"

const int MAX_RENDER_BATCH_SIZE = 1000; // 100 render components allowed per render batch

// ======================================================================================
// Render Batch
// ======================================================================================

template <typename T> class RenderBatch {

protected:
    T m_RenderComponenets[MAX_RENDER_BATCH_SIZE];

    const int m_ZIndex;
    int m_Size;

public:
    RenderBatch(int zIndex) : m_ZIndex(zIndex), m_Size(0) {}

    virtual void AddRenderComponent(T renderComponent) {}
    virtual void Update(const float& deltaTime) {}

    const int& GetZIndex() const { return m_ZIndex; }
    const int& GetSize() const { return m_Size; }
    const T GetRenderComponent(int index) const { return m_RenderComponenets[index]; }

    const bool IsFull() const { m_Size == MAX_RENDER_BATCH_SIZE - 1; }
};

// ======================================================================================
// Mesh2D Render Batch
// ======================================================================================

class Mesh2DRenderBatch : public RenderBatch<MeshRenderer> {

    void AddRenderComponent(MeshRenderer renderComponent) override;
    void Update(const float& deltaTime) override;

};