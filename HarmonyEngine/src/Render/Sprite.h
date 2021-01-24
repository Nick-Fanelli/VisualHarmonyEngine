#pragma once

#include <memory>

#include "Mesh.h"
#include "Texture.h"

struct Sprite {

    std::shared_ptr<Mesh2D> m_Mesh;
    std::shared_ptr<Texture> m_Texture;

    Sprite(std::shared_ptr<Mesh2D> mesh, std::shared_ptr<Texture> texture) : m_Mesh(mesh), m_Texture(texture) {}

};