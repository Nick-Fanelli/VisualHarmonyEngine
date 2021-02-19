#pragma once

#include <GL/glew.h>
#include <GLUT/glut.h>

#include "../Core/Log.h"

namespace HarmonyEngine {

    static const int MIN_FILTER = GL_LINEAR;
    static const int MAG_FILTER = GL_LINEAR;

    struct Quad;

    class Texture {

        GLuint m_TextureID = -1;

        const char* m_Filepath = nullptr;
        int m_Width, m_Height;

    public:
        Texture(const char* filepath) : m_Filepath(filepath) {}

        Texture() {}

        Texture(const Texture&) = default;

        void Initialize();

        void Initialize(const char* filepath, int width, int height);

        void Bind();

        void Unbind();

        const GLuint& GetTextureID() const { return m_TextureID; }

        const char* GetFilepath() const { return m_Filepath; }

        const int& GetWidth() const { return m_Width; }

        const int& GetHeight() const { return m_Height; }
    };

    class SpriteSheet {

        Texture m_Texture;
        int m_SpriteWidth, m_SpriteHeight;
        float m_NormalizedSpriteWidth, m_NormalizedSpriteHeight;

    public:
        SpriteSheet() = default;

        SpriteSheet(const Texture& texture, const int& spriteWidth, const int& spriteHeight)
                : m_Texture(texture), m_SpriteWidth(spriteWidth), m_SpriteHeight(spriteHeight),
                  m_NormalizedSpriteWidth((float) spriteWidth / (float) texture.GetWidth()),
                  m_NormalizedSpriteHeight((float) spriteHeight / (float) texture.GetHeight()) {}

        SpriteSheet(const SpriteSheet&) = default;

        const Texture& GetTexture() const { return m_Texture; }

        const int& GetSpriteWidth() const { return m_SpriteWidth; }

        const int& GetSpriteHeight() const { return m_SpriteHeight; }

        void AssignToSprite(Quad* quad, const int& spriteX, const int& spriteY);
    };

}