#pragma once

#include <memory>

#include "Mesh.h"
#include "Texture.h"

struct Sprite {

    Mesh2D* m_Mesh;
    Texture* m_Texture;

    Sprite(Mesh2D* mesh, Texture* texture) : m_Mesh(mesh), m_Texture(texture) {}

};